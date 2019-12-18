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
typedef  size_t ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_3__ {int Right; int Left; char** MenuItemList; size_t SelectedMenuItem; scalar_t__ Top; } ;
typedef  TYPE_1__* PUI_MENU_INFO ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ UiCenterMenu ; 
 int /*<<< orphan*/  UiDrawText (int,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UiMenuBgColor ; 
 int /*<<< orphan*/  UiMenuFgColor ; 
 int /*<<< orphan*/  UiSelectedTextBgColor ; 
 int /*<<< orphan*/  UiSelectedTextColor ; 
 int /*<<< orphan*/  UiTextColor ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

VOID
TuiDrawMenuItem(PUI_MENU_INFO MenuInfo,
                ULONG MenuItemNumber)
{
    ULONG i;
    CHAR MenuLineText[80];
    ULONG SpaceTotal;
    ULONG SpaceLeft;
    ULONG SpaceRight = 0;
    UCHAR Attribute = ATTR(UiTextColor, UiMenuBgColor);

    //
    // Check if using centered menu
    //
    if (UiCenterMenu)
    {
        //
        // We will want the string centered so calculate
        // how many spaces will be to the left and right
        //
        SpaceTotal = (MenuInfo->Right - MenuInfo->Left - 2) -
                     (ULONG)(MenuInfo->MenuItemList[MenuItemNumber] ?
                             strlen(MenuInfo->MenuItemList[MenuItemNumber]) : 0);
        SpaceLeft = (SpaceTotal / 2) + 1;
        SpaceRight = (SpaceTotal - SpaceLeft) + 1;

        //
        // Insert the spaces on the left
        //
        for (i = 0; i < SpaceLeft; i++) MenuLineText[i] = ' ';
        MenuLineText[i] = '\0';
    }
    else
    {
        //
        // Simply left-align it
        //
        MenuLineText[0] = '\0';
        strcat(MenuLineText, "    ");
    }

    //
    // Now append the text string
    //
    if (MenuInfo->MenuItemList[MenuItemNumber])
        strcat(MenuLineText, MenuInfo->MenuItemList[MenuItemNumber]);

    //
    // Check if using centered menu, and add spaces on the right if so
    //
    if (UiCenterMenu) for (i=0; i < SpaceRight; i++) strcat(MenuLineText, " ");

    //
    // If it is a separator
    //
    if (MenuInfo->MenuItemList[MenuItemNumber] == NULL)
    {
        //
        // Make it a separator line and use menu colors
        //
        memset(MenuLineText, 0, 80);
        memset(MenuLineText, 0xC4, (MenuInfo->Right - MenuInfo->Left - 1));
        Attribute = ATTR(UiMenuFgColor, UiMenuBgColor);
    }
    else if (MenuItemNumber == MenuInfo->SelectedMenuItem)
    {
        //
        // If this is the selected item, use the selected colors
        //
        Attribute = ATTR(UiSelectedTextColor, UiSelectedTextBgColor);
    }

    //
    // Draw the item
    //
    UiDrawText(MenuInfo->Left + 1,
               MenuInfo->Top + 1 + MenuItemNumber,
               MenuLineText,
               Attribute);
}