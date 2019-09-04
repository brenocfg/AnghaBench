#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  style; void* cy; void* y; void* cx; void* x; int /*<<< orphan*/  hOwner; int /*<<< orphan*/  szClass; int /*<<< orphan*/  szTitle; } ;
struct TYPE_4__ {int /*<<< orphan*/  nConsoleCount; } ;
typedef  TYPE_1__* PCONSOLE_MAINFRAME_WND ;
typedef  TYPE_2__ MDICREATESTRUCT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 void* CW_USEDEFAULT ; 
 int /*<<< orphan*/  CreateNewConsoleTitle () ; 
 int /*<<< orphan*/  GetModuleHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MDIS_ALLCHILDSTYLES ; 
 scalar_t__ SendMessage (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_MDICREATE ; 
 int /*<<< orphan*/  szMMCChildFrm ; 

HWND
CreateNewMDIChild(PCONSOLE_MAINFRAME_WND Info,
                  HWND hwndMDIClient)
{
    MDICREATESTRUCT mcs;
    HWND hChild;

    mcs.szTitle = CreateNewConsoleTitle();
    mcs.szClass = szMMCChildFrm;
    mcs.hOwner  = GetModuleHandle(NULL);
    mcs.x = mcs.cx = CW_USEDEFAULT;
    mcs.y = mcs.cy = CW_USEDEFAULT;
    mcs.style = MDIS_ALLCHILDSTYLES;

    hChild = (HWND)SendMessage(hwndMDIClient, WM_MDICREATE, 0, (LPARAM)&mcs);
    if (hChild)
    {
        Info->nConsoleCount++;
    }

    return hChild;
}