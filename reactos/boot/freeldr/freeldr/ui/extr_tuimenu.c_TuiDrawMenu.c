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
struct TYPE_7__ {int /*<<< orphan*/  (* DrawStatusText ) (char*) ;} ;
struct TYPE_6__ {scalar_t__ MenuItemCount; scalar_t__ ShowBootOptions; } ;
typedef  TYPE_1__* PUI_MENU_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  DisplayBootTimeOptions () ; 
 int /*<<< orphan*/  TuiDrawMenuBox (TYPE_1__*) ; 
 int /*<<< orphan*/  TuiDrawMenuItem (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  UiDrawBackdrop () ; 
 TYPE_2__ UiVtbl ; 
 int /*<<< orphan*/  VideoCopyOffScreenBufferToVRAM () ; 
 int /*<<< orphan*/  stub1 (char*) ; 

VOID
TuiDrawMenu(PUI_MENU_INFO MenuInfo)
{
    ULONG i;

    //
    // Draw the backdrop
    //
    UiDrawBackdrop();

    //
    // Update the status bar
    //
    UiVtbl.DrawStatusText("Use \x18 and \x19 to select, then press ENTER.");

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

    /* Display the boot options if needed */
    if (MenuInfo->ShowBootOptions)
    {
        DisplayBootTimeOptions();
    }

    VideoCopyOffScreenBufferToVRAM();
}