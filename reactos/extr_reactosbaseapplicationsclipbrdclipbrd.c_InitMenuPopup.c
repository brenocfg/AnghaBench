#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  hMainWnd; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HMENU ;

/* Variables and functions */
 scalar_t__ CMD_DELETE ; 
 scalar_t__ CMD_SAVE_AS ; 
 scalar_t__ CountClipboardFormats () ; 
 int /*<<< orphan*/  DrawMenuBar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnableMenuItem (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GetMenuItemID (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ Globals ; 
 int /*<<< orphan*/  MF_ENABLED ; 
 int /*<<< orphan*/  MF_GRAYED ; 

__attribute__((used)) static void InitMenuPopup(HMENU hMenu, LPARAM index)
{
    if ((GetMenuItemID(hMenu, 0) == CMD_DELETE) || (GetMenuItemID(hMenu, 1) == CMD_SAVE_AS))
    {
        if (CountClipboardFormats() == 0)
        {
            EnableMenuItem(hMenu, CMD_DELETE, MF_GRAYED);
            EnableMenuItem(hMenu, CMD_SAVE_AS, MF_GRAYED);
        }
        else
        {
            EnableMenuItem(hMenu, CMD_DELETE, MF_ENABLED);
            EnableMenuItem(hMenu, CMD_SAVE_AS, MF_ENABLED);
        }
    }

    DrawMenuBar(Globals.hMainWnd);
}