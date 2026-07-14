#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define WIDTH 700
#define HEIGHT 800


// ----------------------------
// Global calculator variables
// ----------------------------
// ----------------------------
// Graphing function
// ----------------------------

char display[100] = "0";

double storedValue = 0;
char operation = 0;
bool graphMode = false;
int graphType = -1;


// INFO system

bool infoMode = false;
bool popup = false;

char selectedItem[20];


// Font

Font mainFont;


// Colors

Color background = {22,18,32,255};
Color panel = {45,35,65,255};

Color pink = {255,80,160,255};
Color darkPink = {150,35,105,255};




// ----------------------------
// Text drawing helper
// ----------------------------

void drawText(
    char *text,
    float x,
    float y,
    float size,
    Color color
)
{
    DrawTextEx(
        mainFont,
        text,
        (Vector2){x,y},
        size,
        2,
        color
    );
}



void drawGraph()
{
    Rectangle area = {40,190,620,300};

    DrawRectangleRec(area,(Color){25,15,40,255});


    // axes
    DrawLine(40,340,660,340,WHITE);
    DrawLine(350,190,350,490,WHITE);


    char title[30]="";


    if(graphType==0)
        strcpy(title,"y = sin(x)");

    else if(graphType==1)
        strcpy(title,"y = cos(x)");

    else if(graphType==2)
        strcpy(title,"y = tan(x)");

    else if(graphType==3)
        strcpy(title,"y = log(x)");

    else if(graphType==4)
        strcpy(title,"y = ln(x)");

    else if(graphType==5)
        strcpy(title,"y = sqrt(x)");

    else
    {
        strcpy(title,"Choose a function");
        drawText(title,60,210,20,pink);
        return;
    }



    for(int i=1;i<620;i++)
    {

        float x1=(i-1-310)*0.03;
        float x2=(i-310)*0.03;


        float y1;
        float y2;



        if(graphType==0)
        {
            y1=sin(x1);
            y2=sin(x2);
        }

        else if(graphType==1)
        {
            y1=cos(x1);
            y2=cos(x2);
        }

        else if(graphType==2)
        {
            y1=tan(x1);
            y2=tan(x2);
        }

        else if(graphType==3)
        {
            y1=log10(fabs(x1)+0.01);
            y2=log10(fabs(x2)+0.01);
        }

        else if(graphType==4)
        {
            y1=log(fabs(x1)+0.01);
            y2=log(fabs(x2)+0.01);
        }

        else
        {
            y1=sqrt(fabs(x1));
            y2=sqrt(fabs(x2));
        }



        DrawLine(
            40+i-1,
            340-y1*50,
            40+i,
            340-y2*50,
            (Color){190,80,255,255}
        );
    }


    drawText(
        title,
        60,
        210,
        20,
        (Color){0,255,180,255}
    );
}

// ----------------------------
// Add character to display
// ----------------------------

void addCharacter(char c)
{

    if(strcmp(display,"0")==0)
    {
        display[0]='\0';
    }


    int len=strlen(display);

    display[len]=c;
    display[len+1]='\0';

}




// ----------------------------
// Clear calculator
// ----------------------------

void clearCalculator()
{

    strcpy(display,"0");

    storedValue=0;

    operation=0;

}




// ----------------------------
// Calculation engine
// ----------------------------

void calculate()
{

    double num=atof(display);

    double answer=0;



    switch(operation)
    {

        case '+':

            answer=storedValue+num;

            break;


        case '-':

            answer=storedValue-num;

            break;


        case '*':

            answer=storedValue*num;

            break;


        case '/':

            if(num!=0)
                answer=storedValue/num;

            break;

    }



    sprintf(
        display,
        "%.8g",
        answer
    );

}



// ----------------------------
// Scientific functions
// ----------------------------

void scientific(char *function)
{

    double x=atof(display);



    if(strcmp(function,"sin")==0)

        x=sin(x);



    else if(strcmp(function,"cos")==0)

        x=cos(x);



    else if(strcmp(function,"tan")==0)

        x=tan(x);



    else if(strcmp(function,"sqrt")==0)

        x=sqrt(x);



    else if(strcmp(function,"log")==0)

        x=log10(x);



    else if(strcmp(function,"ln")==0)

        x=log(x);



    else if(strcmp(function,"x2")==0)

        x=x*x;



    sprintf(
        display,
        "%.8g",
        x
    );

}





// ----------------------------
// Button drawing
// ----------------------------

void drawButton(
    Rectangle box,
    char *text
)
{

    bool hover =
    CheckCollisionPointRec(
        GetMousePosition(),
        box
    );



    Color buttonColor = darkPink;


// special buttons



if(strcmp(text,"INFO")==0)
{
    buttonColor = (Color){78,110,129,255}; // #4E6E81 Slate
}


else if(strcmp(text,"GRAPH")==0)
{
    buttonColor = (Color){108,122,137,255}; // #6C7A89 Muted Grey-Blue
}


if(hover)
{
   if(strcmp(text,"INFO")==0)
    buttonColor = (Color){100,140,160,255};

else if(strcmp(text,"GRAPH")==0)
    buttonColor = (Color){135,150,165,255};
    else
        buttonColor = pink;
}

DrawRectangleRec(
    box,
    buttonColor
);


    DrawRectangleLinesEx(
        box,
        2,
        WHITE
    );


float textWidth =
MeasureTextEx(
    mainFont,
    text,
    30,
    1
).x;

float textHeight =
MeasureTextEx(
    mainFont,
    text,
    30,
    1
).y;


drawText(
    text,
    box.x + (box.width - textWidth)/2,
    box.y + (box.height - textHeight)/2,
    30,
    WHITE
);


}

// ----------------------------
// Display area
// ----------------------------

void drawDisplay()
{

    DrawRectangle(
        40,
        40,
        620,
        110,
        panel
    );



    drawText(
    display,
    60,
    65,
    55,
    WHITE
);



    if(infoMode)
    {

        drawText(
            "INFO MODE ON",
            470,
            115,
            18,
            pink
        );

    }

}



// ==========================================
// INFO DATABASE
// ==========================================


void drawInfoPage()
{

    // Popup card

    DrawRectangle(
        70,
        130,
        560,
        560,
        panel
    );


    DrawRectangleLinesEx(
        (Rectangle){70,130,560,560},
        3,
        pink
    );



    // Title

    drawText(
        selectedItem,
        110,
        160,
        32,
        pink
    );



    // -------------------------
    // NUMBERS
    // -------------------------


    if(strcmp(selectedItem,"0")==0)
    {
        drawText(
        "ZERO (0)",
        110,220,26,WHITE);


        drawText(
        "Classification:",
        110,270,22,pink);


        drawText(
        "Whole number, Integer",
        110,305,20,WHITE);


        drawText(
        "Properties:",
        110,350,22,pink);


        drawText(
        "Additive identity",
        110,385,20,WHITE);


        drawText(
        "Facts:",
        110,430,22,pink);


        drawText(
        "- Multiplying any number by 0",
        110,465,19,WHITE);


        drawText(
        "  gives 0",
        110,495,19,WHITE);


        drawText(
        "- Developed mathematically",
        110,530,19,WHITE);


        drawText(
        "  in ancient India",
        110,560,19,WHITE);
    }



    else if(strcmp(selectedItem,"1")==0)
    {
        drawText(
        "NUMBER ONE (1)",
        110,220,26,WHITE);


        drawText(
        "Special Property:",
        110,270,22,pink);


        drawText(
        "Multiplicative identity",
        110,305,20,WHITE);


        drawText(
        "Example:",
        110,350,22,pink);


        drawText(
        "8 x 1 = 8",
        110,385,20,WHITE);


        drawText(
        "Facts:",
        110,430,22,pink);


        drawText(
        "- Neither prime nor composite",
        110,465,19,WHITE);


        drawText(
        "- First counting number",
        110,500,19,WHITE);
    }



    else if(strcmp(selectedItem,"2")==0)
    {
        drawText(
        "NUMBER TWO (2)",
        110,220,26,WHITE);


        drawText(
        "Classification:",
        110,270,22,pink);


        drawText(
        "Prime Number",
        110,305,20,WHITE);


        drawText(
        "Unique Facts:",
        110,350,22,pink);


        drawText(
        "- Only even prime number",
        110,390,19,WHITE);


        drawText(
        "- Binary uses 0 and 1",
        110,425,19,WHITE);
    }



    else if(strcmp(selectedItem,"3")==0)
    {
        drawText(
        "NUMBER THREE (3)",
        110,220,26,WHITE);


        drawText(
        "Facts:",
        110,270,22,pink);


        drawText(
        "- Triangle has 3 sides",
        110,310,20,WHITE);


        drawText(
        "- RGB has 3 primary colors",
        110,345,20,WHITE);


        drawText(
        "- First odd prime number",
        110,380,20,WHITE);
    }



    else if(strcmp(selectedItem,"4")==0)
    {
        drawText(
        "NUMBER FOUR (4)",
        110,220,26,WHITE);


        drawText(
        "Facts:",
        110,270,22,pink);


        drawText(
        "- Square has 4 sides",
        110,310,20,WHITE);


        drawText(
        "- DNA contains 4 bases",
        110,345,20,WHITE);


        drawText(
        "- Cube has 6 faces",
        110,380,20,WHITE);
    }



    else if(strcmp(selectedItem,"5")==0)
    {
        drawText(
        "NUMBER FIVE (5)",
        110,220,26,WHITE);


        drawText(
        "Facts:",
        110,270,22,pink);


        drawText(
        "- Humans have 5 fingers",
        110,310,20,WHITE);


        drawText(
        "- Pentagon has 5 sides",
        110,345,20,WHITE);


        drawText(
        "- Base-10 relates to fingers",
        110,380,20,WHITE);
    }



    else if(strcmp(selectedItem,"6")==0)
    {
        drawText(
        "NUMBER SIX (6)",
        110,220,26,WHITE);


        drawText(
        "Facts:",
        110,270,22,pink);


        drawText(
        "- First perfect number",
        110,310,20,WHITE);


        drawText(
        "- Hexagon has 6 sides",
        110,345,20,WHITE);
    }



    else if(strcmp(selectedItem,"7")==0)
    {
        drawText(
        "NUMBER SEVEN (7)",
        110,220,26,WHITE);


        drawText(
        "Facts:",
        110,270,22,pink);


        drawText(
        "- 7 days in a week",
        110,310,20,WHITE);


        drawText(
        "- 7 colors in rainbow",
        110,345,20,WHITE);


        drawText(
        "- 7 musical notes",
        110,380,20,WHITE);
    }



    else if(strcmp(selectedItem,"8")==0)
    {
        drawText(
        "NUMBER EIGHT (8)",
        110,220,26,WHITE);


        drawText(
        "Facts:",
        110,270,22,pink);


        drawText(
        "- 8 bits = 1 byte",
        110,310,20,WHITE);


        drawText(
        "- Octagon has 8 sides",
        110,345,20,WHITE);


        drawText(
        "- Cube has 8 vertices",
        110,380,20,WHITE);
    }



    else if(strcmp(selectedItem,"9")==0)
    {
        drawText(
        "NUMBER NINE (9)",
        110,220,26,WHITE);


        drawText(
        "Facts:",
        110,270,22,pink);


        drawText(
        "- Highest single digit",
        110,310,20,WHITE);


        drawText(
        "- 3x3 creates 9",
        110,345,20,WHITE);


        drawText(
        "- Multiplication has",
        110,380,20,WHITE);


        drawText(
        "  special patterns",
        110,415,20,WHITE);
    }



    // -------------------------
    // SYMBOLS
    // -------------------------


    else if(strcmp(selectedItem,".")==0)
{
    drawText("DECIMAL POINT",110,220,26,WHITE);

    drawText("Meaning:",110,270,22,pink);
    drawText("Separates whole and",110,305,20,WHITE);
    drawText("fractional values.",110,335,20,WHITE);

    drawText("History:",110,380,22,pink);
    drawText("Decimal notation evolved",110,415,20,WHITE);
    drawText("over many centuries and",110,445,20,WHITE);
    drawText("became widely used in",110,475,20,WHITE);
    drawText("Europe during the",110,505,20,WHITE);
    drawText("16th and 17th centuries.",110,535,20,WHITE);

    drawText("Example:",110,580,22,pink);
    drawText("3.14159",110,615,20,WHITE);
}



    else if(strcmp(selectedItem,"=")==0)
    {
        drawText(
        "EQUAL SIGN",
        110,220,26,WHITE);


        drawText(
        "Meaning:",
        110,270,22,pink);


        drawText(
        "Shows both sides have",
        110,310,20,WHITE);


        drawText(
        "the same value.",
        110,340,20,WHITE);


        drawText(
        "Example: 2+3=5",
        110,390,20,WHITE);
    }



    else if(strcmp(selectedItem,"x2")==0)
    {
        drawText(
        "SQUARE FUNCTION",
        110,220,26,WHITE);


        drawText(
        "Formula:",
        110,270,22,pink);


        drawText(
        "x squared = x * x",
        110,310,22,WHITE);


        drawText(
        "Uses:",
        110,360,22,pink);


        drawText(
        "Area, physics, statistics",
        110,400,20,WHITE);
    }

else if(strcmp(selectedItem,"+")==0)
{
    drawText("ADDITION (+)",110,220,26,WHITE);

    drawText("Meaning:",110,270,22,pink);
    drawText("Combines two quantities.",110,305,20,WHITE);

    drawText("History:",110,350,22,pink);
    drawText("The + symbol was",110,385,20,WHITE);
    drawText("popularized by German",110,415,20,WHITE);
    drawText("mathematician Johannes",110,445,20,WHITE);
    drawText("Widmann in 1489.",110,475,20,WHITE);
    drawText("It had earlier uses in",110,505,20,WHITE);
    drawText("merchant writings.",110,535,20,WHITE);

    drawText("Example:",110,580,22,pink);
    drawText("7 + 5 = 12",110,615,20,WHITE);
}
else if(strcmp(selectedItem,"-")==0)
{
    drawText("SUBTRACTION (-)",110,220,26,WHITE);

    drawText("Meaning:",110,270,22,pink);
    drawText("Shows the difference",110,305,20,WHITE);
    drawText("between two values.",110,335,20,WHITE);

    drawText("History:",110,380,22,pink);
    drawText("The - symbol was also",110,415,20,WHITE);
    drawText("popularized by Johannes",110,445,20,WHITE);
    drawText("Widmann in 1489 after",110,475,20,WHITE);
    drawText("earlier commercial use.",110,505,20,WHITE);

    drawText("Example:",110,550,22,pink);
    drawText("10 - 4 = 6",110,585,20,WHITE);
}
else if(strcmp(selectedItem,"*")==0)
{
    drawText("MULTIPLICATION (*)",110,220,26,WHITE);

    drawText("Meaning:",110,270,22,pink);
    drawText("Repeated addition.",110,305,20,WHITE);

    drawText("Example:",110,350,22,pink);
    drawText("4 x 3 = 12",110,385,20,WHITE);

    drawText("Used in:",110,430,22,pink);
    drawText("Scaling, area and physics.",110,465,20,WHITE);
}

else if(strcmp(selectedItem,"=")==0)
{
    drawText("EQUAL SIGN (=)",110,220,26,WHITE);

    drawText("Meaning:",110,270,22,pink);
    drawText("Shows two values are",110,305,20,WHITE);
    drawText("the same.",110,335,20,WHITE);

    drawText("History:",110,380,22,pink);
    drawText("Invented by Robert",110,415,20,WHITE);
    drawText("Recorde in 1557.",110,445,20,WHITE);
    drawText("He said no two things",110,475,20,WHITE);
    drawText("could be more equal",110,505,20,WHITE);
    drawText("than parallel lines.",110,535,20,WHITE);

    drawText("Example:",110,580,22,pink);
    drawText("2 + 3 = 5",110,615,20,WHITE);
}

else if(strcmp(selectedItem,"=")==0)
{
    drawText("EQUAL SIGN (=)",110,220,26,WHITE);

    drawText("Meaning:",110,270,22,pink);
    drawText("Shows two expressions",110,305,20,WHITE);
    drawText("have the same value.",110,335,20,WHITE);

    drawText("History:",110,380,22,pink);
    drawText("Introduced by Welsh",110,415,20,WHITE);
    drawText("mathematician Robert",110,445,20,WHITE);
    drawText("Recorde in 1557.",110,475,20,WHITE);
    drawText("He chose parallel lines",110,505,20,WHITE);
    drawText("because nothing is more",110,535,20,WHITE);
    drawText("equal.",110,565,20,WHITE);
}


else if(strcmp(selectedItem,"/")==0)
{
    drawText("DIVISION (/)",110,220,26,WHITE);

    drawText("Meaning:",110,270,22,pink);
    drawText("Splitting into equal parts.",110,305,20,WHITE);

    drawText("Example:",110,350,22,pink);
    drawText("20 / 4 = 5",110,385,20,WHITE);

    drawText("Used in:",110,430,22,pink);
    drawText("Fractions and averages.",110,465,20,WHITE);
}


else if(strcmp(selectedItem,"sqrt")==0)
{
    drawText("SQUARE ROOT",110,220,26,WHITE);

    drawText("Meaning:",110,270,22,pink);
    drawText("Finds the number that",110,305,20,WHITE);
    drawText("produces a value when",110,335,20,WHITE);
    drawText("multiplied by itself.",110,365,20,WHITE);

    drawText("History:",110,410,22,pink);
    drawText("This symbol appeared",110,445,20,WHITE);
    drawText("in print in 1525 in",110,475,20,WHITE);
    drawText("Christoff Rudolff's",110,505,20,WHITE);
    drawText("algebra book.",110,535,20,WHITE);

    drawText("Example: sqrt(64) = 8",110,580,20,WHITE);
}

else if(strcmp(selectedItem,"log")==0)
{
    drawText("LOGARITHM",110,220,26,WHITE);

    drawText("Meaning:",110,270,22,pink);
    drawText("Finds the exponent",110,305,20,WHITE);
    drawText("needed to produce",110,335,20,WHITE);
    drawText("a number.",110,365,20,WHITE);

    drawText("History:",110,410,22,pink);
    drawText("Invented by Scottish",110,445,20,WHITE);
    drawText("mathematician John Napier in 1614.",110,475,20,WHITE);

    drawText("Fact:",110,550,22,pink);
    drawText("Scientists relied on log tables for centuries.",110,585,20,WHITE);
}

else if(strcmp(selectedItem,"ln")==0)
{
    drawText("NATURAL LOG",110,220,26,WHITE);

    drawText("Meaning:",110,270,22,pink);
    drawText("Logarithm with base e.",110,305,20,WHITE);

    drawText("History:",110,350,22,pink);
    drawText("The natural logarithm",110,385,20,WHITE);
    drawText("is based on the",110,415,20,WHITE);
    drawText("constant e, whose",110,445,20,WHITE);
    drawText("modern notation was",110,475,20,WHITE);
    drawText("popularized by",110,505,20,WHITE);
    drawText("Leonhard Euler.",110,535,20,WHITE);

    drawText("Value: e = 2.71828...",110,585,20,WHITE);
}


else if(strcmp(selectedItem,"sin")==0)
{
    drawText("SINE FUNCTION",110,220,26,WHITE);

    drawText("Meaning:",110,270,22,pink);
    drawText("sin(x) = opposite/hypotenuse",110,305,20,WHITE);
    
    drawText("History:",110,380,22,pink);
    drawText("The modern sine function developed",110,415,20,WHITE);
    drawText("from ancient Indian astronomy and was",110,475,20,WHITE);
    drawText("expanded by Arabic scholars.",110,505,20,WHITE);
    drawText("Use: Waves, physics,engineering",110,535,20,WHITE);
}
else if(strcmp(selectedItem,"cos")==0)
{
    drawText("COSINE FUNCTION",110,220,26,WHITE);

    drawText("Formula:",110,270,22,pink);
    drawText("cos(x)=adjacent/hypotenuse",110,305,20,WHITE);

    drawText("Uses:",110,350,22,pink);
    drawText("Geometry and waves.",110,385,20,WHITE);
}

else if(strcmp(selectedItem,"cos")==0)
{
    drawText("COSINE FUNCTION",110,220,26,WHITE);

    drawText("Formula:",110,270,22,pink);
    drawText("cos(x)=adjacent/hypotenuse",110,305,20,WHITE);

    drawText("Uses:",110,350,22,pink);
    drawText("Geometry and waves.",110,385,20,WHITE);
}



    else
    {
        drawText(
        "Mathematical Function",
        110,240,24,WHITE);


        drawText(
        "Information page coming...",
        110,300,20,WHITE);
    }



    // Close button

    DrawRectangle(
        260,
        620,
        180,
        45,
        darkPink
    );


    drawText(
        "CLOSE",
        305,
        632,
        22,
        WHITE
    );

}



// ==========================================
// MAIN PROGRAM
// ==========================================


int main()
{


    InitWindow(
        WIDTH,
        HEIGHT,
        "Numera - Scientific Learning Calculator"
    );
InitAudioDevice();
SetSoundVolume(buttonSound, 1.0f);
    SetTargetFPS(60);



    // Load font

    mainFont =
    LoadFont("Poppins-Regular.ttf");

    Sound buttonSound;
    buttonSound = LoadSound("click.wav");
    PlaySound(buttonSound);
    SetSoundVolume(buttonSound, 1.0f);
    if(buttonSound.frameCount == 0)
{
    printf("SOUND FAILED\n");
}
else
{
    printf("SOUND LOADED\n");
}

if(mainFont.texture.id == 0)
{
    printf("FONT FAILED\n");
}
else
{
    printf("FONT LOADED\n");
}

    char buttons[5][5][10] =
    {

        {"sin","cos","tan","sqrt","INFO"},

        {"7","8","9","/","log"},

        {"4","5","6","*","ln"},

        {"1","2","3","-","GRAPH"},

        {"0",".","=","+","C"}

    };




    while(!WindowShouldClose())
    {

        BeginDrawing();


        ClearBackground(background);



        drawDisplay();
        if(graphMode)
{
    drawGraph();
}




        // Draw calculator buttons

        for(int row=0; row<5; row++)
        {

            for(int col=0; col<5; col++)
            {


                Rectangle button =
                {
                    40 + col*125,
graphMode ? 510 + row*55 : 190 + row*90,
105,
45
                };



                drawButton(
                    button,
                    buttons[row][col]
                );




                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)
                &&
                CheckCollisionPointRec(
                    GetMousePosition(),
                    button))
                {
    PlaySound(buttonSound);
                    char *pressed =
                    buttons[row][col];



                    // INFO MODE BUTTON

                    if(strcmp(pressed,"INFO")==0)
                    {

                        infoMode=!infoMode;

                    }
                    else if(strcmp(pressed,"GRAPH")==0)
{
    graphMode = !graphMode;

    if(graphMode)
        graphType = -1;
}



                    // CLEAR

                    else if(strcmp(pressed,"C")==0)
                    {

                        clearCalculator();

                    }



                    // EQUAL

                    else if(strcmp(pressed,"=")==0)
                    {


                        if(infoMode)
                        {

                            strcpy(
                            selectedItem,
                            "="
                            );

                            popup=true;

                        }

                        else
                        {
                            calculate();
                        }

                    }




                    // Scientific buttons

                    else if(
strcmp(pressed,"sin")==0 ||
strcmp(pressed,"cos")==0 ||
strcmp(pressed,"tan")==0 ||
strcmp(pressed,"sqrt")==0 ||
strcmp(pressed,"log")==0 ||
strcmp(pressed,"ln")==0
)
                    
                    {
                        if(graphMode)
{
    if(strcmp(pressed,"sin")==0)
        graphType=0;

    else if(strcmp(pressed,"cos")==0)
        graphType=1;

    else if(strcmp(pressed,"tan")==0)
        graphType=2;

    else if(strcmp(pressed,"log")==0)
        graphType=3;

    else if(strcmp(pressed,"ln")==0)
        graphType=4;

    else if(strcmp(pressed,"sqrt")==0)
        graphType=5;
}



                        if(infoMode)
                        {

                            strcpy(
                            selectedItem,
                            pressed
                            );


                            popup=true;

                        }

                        else if(!graphMode)
{
    scientific(pressed);
}

                    }





                    // Operators

                    else if(
                    strcmp(pressed,"+")==0 ||
                    strcmp(pressed,"-")==0 ||
                    strcmp(pressed,"*")==0 ||
                    strcmp(pressed,"/")==0
                    )
                    {


                        if(infoMode)
                        {

                            strcpy(
                            selectedItem,
                            pressed
                            );


                            popup=true;

                        }

                        else
                        {

                            storedValue =
                            atof(display);


                            operation =
                            pressed[0];


                            strcpy(
                            display,
                            "0"
                            );

                        }


                    }





                    // Numbers and decimal

                    else
                    {


                        if(infoMode)
                        {


                            strcpy(
                            selectedItem,
                            pressed
                            );


                            popup=true;


                        }

                        else
                        {

                            addCharacter(
                            pressed[0]
                            );

                        }


                    }



                }


            }

        }





        // INFO POPUP

        if(popup)
        {

            drawInfoPage();



            Rectangle closeButton =
            {
                260,
                620,
                180,
                45
            };



            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)
            &&
            CheckCollisionPointRec(
                GetMousePosition(),
                closeButton))
            {

                popup=false;

            }


        }




        drawText(
        "Numera - Scientific Learning Calculator",
        155,
        730,
        20,
        LIGHTGRAY);



        EndDrawing();

    }




UnloadSound(buttonSound);
UnloadFont(mainFont);

CloseAudioDevice();

CloseWindow();

    return 0;

}