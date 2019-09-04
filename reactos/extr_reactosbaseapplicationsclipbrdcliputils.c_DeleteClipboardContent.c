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

/* Variables and functions */
 int /*<<< orphan*/  CloseClipboard () ; 
 int /*<<< orphan*/  EmptyClipboard () ; 
 TYPE_1__ Globals ; 
 int /*<<< orphan*/  OpenClipboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowLastWin32Error (int /*<<< orphan*/ ) ; 

void DeleteClipboardContent(void)
{
    if (!OpenClipboard(Globals.hMainWnd))
    {
        ShowLastWin32Error(Globals.hMainWnd);
        return;
    }

    if (!EmptyClipboard())
    {
        ShowLastWin32Error(Globals.hMainWnd);
    }

    CloseClipboard();
}