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
struct TYPE_3__ {scalar_t__ nNumGrouping; } ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  TYPE_1__* PGLOBALDATA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CB_ADDSTRING ; 
 int /*<<< orphan*/  CB_RESETCONTENT ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDC_NUMBERSDGROUPING ; 
 int /*<<< orphan*/ * InsSpacesFmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t MAX_FIELD_DIG_SAMPLES ; 
 int /*<<< orphan*/  SAMPLE_NUMBER ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lpFieldDigNumSamples ; 

__attribute__((used)) static VOID
InitFieldDigNumCB(HWND hwndDlg, PGLOBALDATA pGlobalData)
{
    PWSTR pszFieldDigNumSmpl;
    INT nCBIndex;

    /* Clear all box content */
    SendDlgItemMessageW(hwndDlg, IDC_NUMBERSDGROUPING,
                        CB_RESETCONTENT,
                        (WPARAM)0,
                        (LPARAM)0);

    /* Create standard list of field digits num */
    for (nCBIndex = 0; nCBIndex < MAX_FIELD_DIG_SAMPLES; nCBIndex++)
    {
        pszFieldDigNumSmpl = InsSpacesFmt(SAMPLE_NUMBER, lpFieldDigNumSamples[nCBIndex]);
        if (pszFieldDigNumSmpl != NULL)
        {
            SendDlgItemMessageW(hwndDlg, IDC_NUMBERSDGROUPING,
                                CB_ADDSTRING,
                                0,
                                (LPARAM)pszFieldDigNumSmpl);
            HeapFree(GetProcessHeap(), 0, pszFieldDigNumSmpl);
        }
    }

    SendDlgItemMessageW(hwndDlg, IDC_NUMBERSDGROUPING,
                        CB_SETCURSEL,
                        (WPARAM)pGlobalData->nNumGrouping,
                        (LPARAM)0);
}