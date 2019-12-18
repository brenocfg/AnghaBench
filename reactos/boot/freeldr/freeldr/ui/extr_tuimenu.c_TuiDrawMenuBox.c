#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int ULONG ;
struct TYPE_3__ {int Left; int Right; scalar_t__ MenuTimeRemaining; int MenuItemCount; scalar_t__ Top; int /*<<< orphan*/ ** MenuItemList; scalar_t__ Bottom; } ;
typedef  TYPE_1__* PUI_MENU_INFO ;
typedef  int /*<<< orphan*/  MenuLineText ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D_HORZ ; 
 int /*<<< orphan*/  D_VERT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ UiCenterMenu ; 
 int /*<<< orphan*/  UiDrawBox (int,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UiDrawText (int,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UiMenuBgColor ; 
 scalar_t__ UiMenuBox ; 
 int /*<<< orphan*/  UiMenuFgColor ; 
 char* UiTimeText ; 
 int /*<<< orphan*/  _itoa (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

VOID
TuiDrawMenuBox(PUI_MENU_INFO MenuInfo)
{
    CHAR MenuLineText[80], TempString[80];
    ULONG i;

    //
    // Draw the menu box if requested
    //
    if (UiMenuBox)
    {
        UiDrawBox(MenuInfo->Left,
                  MenuInfo->Top,
                  MenuInfo->Right,
                  MenuInfo->Bottom,
                  D_VERT,
                  D_HORZ,
                  FALSE,        // Filled
                  TRUE,         // Shadow
                  ATTR(UiMenuFgColor, UiMenuBgColor));
    }

    //
    // If there is a timeout draw the time remaining
    //
    if (MenuInfo->MenuTimeRemaining >= 0)
    {
        //
        // Copy the integral time text string, and remove the last 2 chars
        //
        strcpy(TempString, UiTimeText);
        i = (ULONG)strlen(TempString);
        TempString[i - 2] = 0;

        //
        // Display the first part of the string and the remaining time
        //
        strcpy(MenuLineText, TempString);
        _itoa(MenuInfo->MenuTimeRemaining, TempString, 10);
        strcat(MenuLineText, TempString);

        //
        // Add the last 2 chars
        //
        strcat(MenuLineText, &UiTimeText[i - 2]);

        //
        // Check if this is a centered menu
        //
        if (UiCenterMenu)
        {
            //
            // Display it in the center of the menu
            //
            UiDrawText(MenuInfo->Right - (ULONG)strlen(MenuLineText) - 1,
                       MenuInfo->Bottom,
                       MenuLineText,
                       ATTR(UiMenuFgColor, UiMenuBgColor));
        }
        else
        {
            //
            // Display under the menu directly
            //
            UiDrawText(0,
                       MenuInfo->Bottom + 4,
                       MenuLineText,
                       ATTR(UiMenuFgColor, UiMenuBgColor));
        }
    }
    else
    {
        //
        // Erase the timeout string with spaces, and 0-terminate for sure
        //
        for (i=0; i<sizeof(MenuLineText)-1; i++)
        {
            MenuLineText[i] = ' ';
        }
        MenuLineText[sizeof(MenuLineText)-1] = 0;

        //
        // Draw this "empty" string to erase
        //
        if (UiCenterMenu)
        {
            UiDrawText(MenuInfo->Right - (ULONG)strlen(MenuLineText) - 1,
                       MenuInfo->Bottom,
                       MenuLineText,
                       ATTR(UiMenuFgColor, UiMenuBgColor));
        }
        else
        {
            UiDrawText(0,
                       MenuInfo->Bottom + 4,
                       MenuLineText,
                       ATTR(UiMenuFgColor, UiMenuBgColor));
        }
    }

    //
    // Loop each item
    //
    for (i = 0; i < MenuInfo->MenuItemCount; i++)
    {
        //
        // Check if it's a separator
        //
        if (MenuInfo->MenuItemList[i] == NULL)
        {
            //
            // Draw the separator line
            //
            UiDrawText(MenuInfo->Left,
                       MenuInfo->Top + i + 1,
                       "\xC7",
                       ATTR(UiMenuFgColor, UiMenuBgColor));
            UiDrawText(MenuInfo->Right,
                       MenuInfo->Top + i + 1,
                       "\xB6",
                       ATTR(UiMenuFgColor, UiMenuBgColor));
        }
    }
}