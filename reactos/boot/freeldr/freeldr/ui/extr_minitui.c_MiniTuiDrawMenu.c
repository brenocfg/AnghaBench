#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ ULONG ;
struct TYPE_7__ {int /*<<< orphan*/  (* DrawText ) (int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {char* MenuHeader; char* MenuFooter; scalar_t__ MenuItemCount; scalar_t__ ShowBootOptions; scalar_t__ Bottom; scalar_t__ Top; } ;
typedef  TYPE_1__* PUI_MENU_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DisplayBootTimeOptions () ; 
 int /*<<< orphan*/  TuiDrawMenuBox (TYPE_1__*) ; 
 int /*<<< orphan*/  TuiDrawMenuItem (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  UiDrawBackdrop () ; 
 int /*<<< orphan*/  UiMenuBgColor ; 
 int /*<<< orphan*/  UiMenuFgColor ; 
 scalar_t__ UiScreenHeight ; 
 TYPE_2__ UiVtbl ; 
 int /*<<< orphan*/  VideoCopyOffScreenBufferToVRAM () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ) ; 

VOID
MiniTuiDrawMenu(PUI_MENU_INFO MenuInfo)
{
    ULONG i;

    //
    // Draw the backdrop
    //
    UiDrawBackdrop();

    //
    // No GUI status bar text, just minimal text. Show the menu header.
    //
    if (MenuInfo->MenuHeader)
    {
        UiVtbl.DrawText(0,
                        MenuInfo->Top - 2,
                        MenuInfo->MenuHeader,
                        ATTR(UiMenuFgColor, UiMenuBgColor));
    }

    //
    // Now tell the user how to choose
    //
    UiVtbl.DrawText(0,
                    MenuInfo->Bottom + 1,
                    "Use \x18 and \x19 to move the highlight to your choice.",
                    ATTR(UiMenuFgColor, UiMenuBgColor));
    UiVtbl.DrawText(0,
                    MenuInfo->Bottom + 2,
                    "Press ENTER to choose.",
                    ATTR(UiMenuFgColor, UiMenuBgColor));

    //
    // And show the menu footer
    //
    if (MenuInfo->MenuFooter)
    {
        UiVtbl.DrawText(0,
                        UiScreenHeight - 4,
                        MenuInfo->MenuFooter,
                        ATTR(UiMenuFgColor, UiMenuBgColor));
    }

    //
    // Draw the menu box
    //
    TuiDrawMenuBox(MenuInfo);

    //
    // Draw each line of the menu
    //
    for (i = 0; i < MenuInfo->MenuItemCount; i++)
    {
        TuiDrawMenuItem(MenuInfo, i);
    }

    //
    // Display the boot options if needed
    //
    if (MenuInfo->ShowBootOptions)
    {
        DisplayBootTimeOptions();
    }

    VideoCopyOffScreenBufferToVRAM();
}