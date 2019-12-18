#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_6__ {int nSplitPos; int /*<<< orphan*/ * hListWnd; int /*<<< orphan*/ * hTreeWnd; int /*<<< orphan*/ * hAddressBtnWnd; int /*<<< orphan*/ * hAddressBarWnd; } ;
struct TYPE_5__ {int bottom; int top; int const left; int const right; } ;
typedef  TYPE_1__ RECT ;
typedef  scalar_t__ HDWP ;

/* Variables and functions */
 scalar_t__ BeginDeferWindowPos (int) ; 
 scalar_t__ DeferWindowPos (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const,int,int const,int const,int const) ; 
 int /*<<< orphan*/  EndDeferWindowPos (scalar_t__) ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  SM_CYEDGE ; 
 int SPLIT_WIDTH ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SetRect (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* g_pChildWnd ; 
 int /*<<< orphan*/ * hStatusBar ; 

extern void ResizeWnd(int cx, int cy)
{
    HDWP hdwp = BeginDeferWindowPos(4);
    RECT rt, rs, rb;
    const int nButtonWidth = 44;
    const int nButtonHeight = 22;
    int cyEdge = GetSystemMetrics(SM_CYEDGE);
    const UINT uFlags = SWP_NOZORDER | SWP_NOACTIVATE;
    SetRect(&rt, 0, 0, cx, cy);
    cy = 0;
    if (hStatusBar != NULL)
    {
        GetWindowRect(hStatusBar, &rs);
        cy = rs.bottom - rs.top;
    }
    GetWindowRect(g_pChildWnd->hAddressBtnWnd, &rb);
    cx = g_pChildWnd->nSplitPos + SPLIT_WIDTH / 2;
    if (hdwp)
        hdwp = DeferWindowPos(hdwp, g_pChildWnd->hAddressBarWnd, NULL,
                              rt.left, rt.top,
                              rt.right - rt.left - nButtonWidth, nButtonHeight,
                              uFlags);
    if (hdwp)
        hdwp = DeferWindowPos(hdwp, g_pChildWnd->hAddressBtnWnd, NULL,
                              rt.right - nButtonWidth, rt.top,
                              nButtonWidth, nButtonHeight,
                              uFlags);
    if (hdwp)
        hdwp = DeferWindowPos(hdwp, g_pChildWnd->hTreeWnd, NULL,
                              rt.left,
                              rt.top + nButtonHeight + cyEdge,
                              g_pChildWnd->nSplitPos - SPLIT_WIDTH/2 - rt.left,
                              rt.bottom - rt.top - cy - 2 * cyEdge,
                              uFlags);
    if (hdwp)
        hdwp = DeferWindowPos(hdwp, g_pChildWnd->hListWnd, NULL,
                              rt.left + cx,
                              rt.top + nButtonHeight + cyEdge,
                              rt.right - cx,
                              rt.bottom - rt.top - cy - 2 * cyEdge,
                              uFlags);
    if (hdwp)
        EndDeferWindowPos(hdwp);
}