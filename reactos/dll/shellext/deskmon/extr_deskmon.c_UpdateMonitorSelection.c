#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int dwMonitorCount; int /*<<< orphan*/ * SelMonitor; int /*<<< orphan*/  hwndDlg; int /*<<< orphan*/ * Monitors; } ;
typedef  TYPE_1__* PDESKMONITOR ;
typedef  int /*<<< orphan*/ * PDESKMONINFO ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_MONITORLIST ; 
 int /*<<< orphan*/  IDC_MONITORPROPERTIES ; 
 int /*<<< orphan*/  LB_GETCURSEL ; 
 int /*<<< orphan*/  LB_GETITEMDATA ; 
 scalar_t__ SendDlgItemMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
UpdateMonitorSelection(PDESKMONITOR This)
{
    INT i;

    if (This->dwMonitorCount > 1)
    {
        This->SelMonitor = NULL;

        i = (INT)SendDlgItemMessage(This->hwndDlg,
                                    IDC_MONITORLIST,
                                    LB_GETCURSEL,
                                    0,
                                    0);
        if (i >= 0)
        {
            This->SelMonitor = (PDESKMONINFO)SendDlgItemMessage(This->hwndDlg,
                                                                IDC_MONITORLIST,
                                                                LB_GETITEMDATA,
                                                                (WPARAM)i,
                                                                0);
        }
    }
    else
        This->SelMonitor = This->Monitors;

    EnableWindow(GetDlgItem(This->hwndDlg,
                            IDC_MONITORPROPERTIES),
                 This->SelMonitor != NULL);
}