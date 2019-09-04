#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mi ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int UINT ;
struct TYPE_9__ {int right; int left; int bottom; int top; } ;
struct TYPE_7__ {int left; int right; int top; int bottom; } ;
struct TYPE_8__ {int cbSize; TYPE_1__ rcMonitor; TYPE_1__ rcWork; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ MONITORINFO ;
typedef  TYPE_3__* LPRECT ;
typedef  int /*<<< orphan*/  HMONITOR ;

/* Variables and functions */
 int /*<<< orphan*/  GetMonitorInfo (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int MONITOR_CENTER ; 
 int /*<<< orphan*/  MONITOR_DEFAULTTONEAREST ; 
 int MONITOR_WORKAREA ; 
 int /*<<< orphan*/  MonitorFromRect (TYPE_3__*,int /*<<< orphan*/ ) ; 
 void* max (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int) ; 

VOID ClipOrCenterRectToMonitor(LPRECT prc, UINT flags)
{
    HMONITOR    hMonitor;
    MONITORINFO mi;
    RECT        rc;
    int         w = prc->right  - prc->left;
    int         h = prc->bottom - prc->top;

    //
    // Get the nearest monitor to the passed rect.
    //
    hMonitor = MonitorFromRect(prc, MONITOR_DEFAULTTONEAREST);

    //
    // Get the work area or entire monitor rect.
    //
    mi.cbSize = sizeof(mi);
    GetMonitorInfo(hMonitor, &mi);

    if (flags & MONITOR_WORKAREA)
        rc = mi.rcWork;
    else
        rc = mi.rcMonitor;

    //
    // Center or clip the passed rect to the monitor rect.
    //
    if (flags & MONITOR_CENTER)
    {
        prc->left   = rc.left + (rc.right  - rc.left - w) / 2;
        prc->top    = rc.top  + (rc.bottom - rc.top  - h) / 2;
        prc->right  = prc->left + w;
        prc->bottom = prc->top  + h;
    }
    else
    {
        prc->left   = max(rc.left, min(rc.right-w,  prc->left));
        prc->top    = max(rc.top,  min(rc.bottom-h, prc->top));
        prc->right  = prc->left + w;
        prc->bottom = prc->top  + h;
    }
}