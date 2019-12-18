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
struct TYPE_3__ {size_t MenuItemCount; size_t Left; size_t Top; size_t Right; size_t Bottom; scalar_t__* MenuItemList; } ;
typedef  TYPE_1__* PUI_MENU_INFO ;

/* Variables and functions */
 size_t TUI_TITLE_BOX_CHAR_HEIGHT ; 
 scalar_t__ UiCenterMenu ; 
 size_t UiScreenHeight ; 
 size_t UiScreenWidth ; 
 scalar_t__ strlen (scalar_t__) ; 

VOID
TuiCalcMenuBoxSize(PUI_MENU_INFO MenuInfo)
{
    ULONG i;
    ULONG Width = 0;
    ULONG Height;
    ULONG Length;

    //
    // Height is the menu item count plus 2 (top border & bottom border)
    //
    Height = MenuInfo->MenuItemCount + 2;
    Height -= 1; // Height is zero-based

    //
    // Loop every item
    //
    for(i = 0; i < MenuInfo->MenuItemCount; i++)
    {
        //
        // Get the string length and make it become the new width if necessary
        //
        if (MenuInfo->MenuItemList[i])
        {
            Length = (ULONG)strlen(MenuInfo->MenuItemList[i]);
            if (Length > Width) Width = Length;
        }
    }

    //
    // Allow room for left & right borders, plus 8 spaces on each side
    //
    Width += 18;

    //
    // Check if we're drawing a centered menu
    //
    if (UiCenterMenu)
    {
        //
        // Calculate the menu box area for a centered menu
        //
        MenuInfo->Left = (UiScreenWidth - Width) / 2;
        MenuInfo->Top = (((UiScreenHeight - TUI_TITLE_BOX_CHAR_HEIGHT) -
                          Height) / 2) + TUI_TITLE_BOX_CHAR_HEIGHT;
    }
    else
    {
        //
        // Put the menu in the default left-corner position
        //
        MenuInfo->Left = -1;
        MenuInfo->Top = 4;
    }

    //
    // The other margins are the same
    //
    MenuInfo->Right = (MenuInfo->Left) + Width;
    MenuInfo->Bottom = (MenuInfo->Top) + Height;
}