#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  hWnd; } ;
struct TYPE_7__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_6__ {scalar_t__ top; scalar_t__ bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__* PRECT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ IsWindowVisible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MoveWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetupStatusBar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__* g_pChildWnd ; 
 int /*<<< orphan*/  hStatusBar ; 

__attribute__((used)) static void resize_frame_rect(HWND hWnd, PRECT prect)
{
    RECT rt;
    /*
    	if (IsWindowVisible(hToolBar)) {
    		SendMessageW(hToolBar, WM_SIZE, 0, 0);
    		GetClientRect(hToolBar, &rt);
    		prect->top = rt.bottom+3;
    		prect->bottom -= rt.bottom+3;
    	}
     */
    if (IsWindowVisible(hStatusBar))
    {
        SetupStatusBar(hWnd, TRUE);
        GetWindowRect(hStatusBar, &rt);
        prect->bottom -= rt.bottom - rt.top;
    }
    MoveWindow(g_pChildWnd->hWnd, prect->left, prect->top, prect->right, prect->bottom, TRUE);
}