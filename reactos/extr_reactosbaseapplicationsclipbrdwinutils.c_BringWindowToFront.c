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
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 scalar_t__ IsIconic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW_RESTORE ; 
 int /*<<< orphan*/  SetForegroundWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void BringWindowToFront(HWND hWnd)
{
    if (IsIconic(hWnd))
    {
        ShowWindow(hWnd, SW_RESTORE);
        SetForegroundWindow(hWnd);
    }
    else
    {
        SetForegroundWindow(hWnd);
    }
}