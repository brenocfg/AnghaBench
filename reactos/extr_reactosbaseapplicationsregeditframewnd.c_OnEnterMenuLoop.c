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
typedef  int WPARAM ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  SB_SETPARTS ; 
 int /*<<< orphan*/  SB_SETTEXTW ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UNREFERENCED_PARAMETER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bInMenuLoop ; 
 int /*<<< orphan*/  hStatusBar ; 

__attribute__((used)) static void OnEnterMenuLoop(HWND hWnd)
{
    int nParts;
    UNREFERENCED_PARAMETER(hWnd);

    /* Update the status bar pane sizes */
    nParts = -1;
    SendMessageW(hStatusBar, SB_SETPARTS, 1, (LPARAM)&nParts);
    bInMenuLoop = TRUE;
    SendMessageW(hStatusBar, SB_SETTEXTW, (WPARAM)0, (LPARAM)L"");
}