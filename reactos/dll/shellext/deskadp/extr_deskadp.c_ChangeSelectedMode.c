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
struct TYPE_3__ {int /*<<< orphan*/ * lpSelDevMode; } ;
typedef  int /*<<< orphan*/ * PDEVMODEW ;
typedef  TYPE_1__* PDESKDISPLAYADAPTER ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IDC_ALLVALIDMODES ; 
 int /*<<< orphan*/  LB_GETCURSEL ; 
 int /*<<< orphan*/  LB_GETITEMDATA ; 
 scalar_t__ SendDlgItemMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL
ChangeSelectedMode(PDESKDISPLAYADAPTER This,
                   HWND hwndListAllModesDlg)
{
    INT i;
    PDEVMODEW lpSelDevMode = NULL;
    BOOL bRet = FALSE;

    i = (INT)SendDlgItemMessage(hwndListAllModesDlg,
                                IDC_ALLVALIDMODES,
                                LB_GETCURSEL,
                                0,
                                0);

    if (i >= 0)
    {
        lpSelDevMode = (PDEVMODEW)SendDlgItemMessage(hwndListAllModesDlg,
                                                     IDC_ALLVALIDMODES,
                                                     LB_GETITEMDATA,
                                                     (WPARAM)i,
                                                     0);
    }

    if (lpSelDevMode != NULL)
    {
        This->lpSelDevMode = lpSelDevMode;
        bRet = TRUE;
    }

    return bRet;
}