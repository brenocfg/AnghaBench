#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t ULONG ;
typedef  size_t SIZE_T ;
typedef  char* PCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HORZ ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UiDrawBox (size_t,size_t,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UiDrawCenteredText (size_t,size_t,size_t,size_t,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UiMenuBgColor ; 
 int /*<<< orphan*/  UiMenuFgColor ; 
 int UiScreenHeight ; 
 int UiScreenWidth ; 
 int /*<<< orphan*/  UiTextColor ; 
 int /*<<< orphan*/  VERT ; 
 size_t strlen (char*) ; 

VOID UiInfoBox(PCSTR MessageText)
{
    SIZE_T        TextLength;
    ULONG        BoxWidth;
    ULONG        BoxHeight;
    ULONG        LineBreakCount;
    SIZE_T        Index;
    SIZE_T        LastIndex;
    ULONG        Left;
    ULONG        Top;
    ULONG        Right;
    ULONG        Bottom;

    TextLength = strlen(MessageText);

    // Count the new lines and the box width
    LineBreakCount = 0;
    BoxWidth = 0;
    LastIndex = 0;
    for (Index=0; Index<TextLength; Index++)
    {
        if (MessageText[Index] == '\n')
        {
            LastIndex = Index;
            LineBreakCount++;
        }
        else
        {
            if ((Index - LastIndex) > BoxWidth)
            {
                BoxWidth = (ULONG)(Index - LastIndex);
            }
        }
    }

    // Calc the box width & height
    BoxWidth += 6;
    BoxHeight = LineBreakCount + 4;

    // Calc the box coordinates
    Left = (UiScreenWidth / 2) - (BoxWidth / 2);
    Top =(UiScreenHeight / 2) - (BoxHeight / 2);
    Right = (UiScreenWidth / 2) + (BoxWidth / 2);
    Bottom = (UiScreenHeight / 2) + (BoxHeight / 2);

    // Draw the box
    UiDrawBox(Left,
              Top,
              Right,
              Bottom,
              VERT,
              HORZ,
              TRUE,
              TRUE,
              ATTR(UiMenuFgColor, UiMenuBgColor)
              );

    // Draw the text
    UiDrawCenteredText(Left, Top, Right, Bottom, MessageText, ATTR(UiTextColor, UiMenuBgColor));
}