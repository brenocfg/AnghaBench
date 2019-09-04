#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ (* UiMenuKeyPressFilterCallback ) (scalar_t__) ;
typedef  scalar_t__ ULONG ;
struct TYPE_8__ {void** MenuItemList; int MenuTimeRemaining; scalar_t__ SelectedMenuItem; scalar_t__ MenuItemCount; scalar_t__ ShowBootOptions; void* MenuFooter; void* MenuHeader; } ;
typedef  TYPE_1__ UI_MENU_INFO ;
struct TYPE_10__ {scalar_t__ Second; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* DrawMenu ) (TYPE_1__*) ;} ;
typedef  void* PCSTR ;
typedef  int LONG ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 TYPE_7__* ArcGetTime () ; 
 scalar_t__ FALSE ; 
 scalar_t__ KEY_ENTER ; 
 scalar_t__ KEY_ESC ; 
 scalar_t__ MachConsGetCh () ; 
 scalar_t__ MachConsKbHit () ; 
 int /*<<< orphan*/  MachHwIdle () ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  TuiCalcMenuBoxSize (TYPE_1__*) ; 
 int /*<<< orphan*/  TuiDrawMenuBox (TYPE_1__*) ; 
 scalar_t__ TuiProcessMenuKeyboardEvent (TYPE_1__*,scalar_t__ (*) (scalar_t__)) ; 
 int /*<<< orphan*/  TuiUpdateDateTime () ; 
 TYPE_3__ UiVtbl ; 
 int /*<<< orphan*/  VideoCopyOffScreenBufferToVRAM () ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

BOOLEAN
TuiDisplayMenu(PCSTR MenuHeader,
               PCSTR MenuFooter,
               BOOLEAN ShowBootOptions,
               PCSTR MenuItemList[],
               ULONG MenuItemCount,
               ULONG DefaultMenuItem,
               LONG MenuTimeOut,
               ULONG* SelectedMenuItem,
               BOOLEAN CanEscape,
               UiMenuKeyPressFilterCallback KeyPressFilter)
{
    UI_MENU_INFO MenuInformation;
    ULONG LastClockSecond;
    ULONG CurrentClockSecond;
    ULONG KeyPress;

    //
    // Before taking any default action if there is no timeout,
    // check whether the supplied key filter callback function
    // may handle a specific user keypress. If it does, the
    // timeout is cancelled.
    //
    if (!MenuTimeOut && KeyPressFilter && MachConsKbHit())
    {
        //
        // Get the key
        //
        KeyPress = MachConsGetCh();

        //
        // Is it extended? Then get the extended key
        //
        if (!KeyPress) KeyPress = MachConsGetCh();

        //
        // Call the supplied key filter callback function to see
        // if it is going to handle this keypress.
        //
        if (KeyPressFilter(KeyPress))
        {
            //
            // It processed the key character, cancel the timeout
            //
            MenuTimeOut = -1;
        }
    }

    //
    // Check if there's no timeout
    //
    if (!MenuTimeOut)
    {
        //
        // Return the default selected item
        //
        if (SelectedMenuItem) *SelectedMenuItem = DefaultMenuItem;
        return TRUE;
    }

    //
    // Setup the MENU_INFO structure
    //
    MenuInformation.MenuHeader = MenuHeader;
    MenuInformation.MenuFooter = MenuFooter;
    MenuInformation.ShowBootOptions = ShowBootOptions;
    MenuInformation.MenuItemList = MenuItemList;
    MenuInformation.MenuItemCount = MenuItemCount;
    MenuInformation.MenuTimeRemaining = MenuTimeOut;
    MenuInformation.SelectedMenuItem = DefaultMenuItem;

    //
    // Calculate the size of the menu box
    //
    TuiCalcMenuBoxSize(&MenuInformation);

    //
    // Draw the menu
    //
    UiVtbl.DrawMenu(&MenuInformation);

    //
    // Get the current second of time
    //
    LastClockSecond = ArcGetTime()->Second;

    //
    // Process keys
    //
    while (TRUE)
    {
        //
        // Process key presses
        //
        KeyPress = TuiProcessMenuKeyboardEvent(&MenuInformation,
                                               KeyPressFilter);

        //
        // Check for ENTER or ESC
        //
        if (KeyPress == KEY_ENTER) break;
        if (CanEscape && KeyPress == KEY_ESC) return FALSE;

        //
        // Update the date & time
        //
        TuiUpdateDateTime();
        VideoCopyOffScreenBufferToVRAM();

        //
        // Check if there is a countdown
        //
        if (MenuInformation.MenuTimeRemaining > 0)
        {
            //
            // Get the updated time, seconds only
            //
            CurrentClockSecond = ArcGetTime()->Second;

            //
            // Check if more then a second has now elapsed
            //
            if (CurrentClockSecond != LastClockSecond)
            {
                //
                // Update the time information
                //
                LastClockSecond = CurrentClockSecond;
                MenuInformation.MenuTimeRemaining--;

                //
                // Update the menu
                //
                TuiDrawMenuBox(&MenuInformation);
                VideoCopyOffScreenBufferToVRAM();
            }
        }
        else if (MenuInformation.MenuTimeRemaining == 0)
        {
            //
            // A time out occurred, exit this loop and return default OS
            //
            break;
        }

        MachHwIdle();
    }

    //
    // Return the selected item
    //
    if (SelectedMenuItem) *SelectedMenuItem = MenuInformation.SelectedMenuItem;
    return TRUE;
}