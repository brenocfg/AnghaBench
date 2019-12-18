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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {scalar_t__ nNumMeasure; } ;
typedef  TYPE_1__* PGLOBALDATA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CB_ADDSTRING ; 
 int /*<<< orphan*/  CB_RESETCONTENT ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  IDC_NUMBERSMEASSYS ; 
 scalar_t__ IDS_METRIC ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ MAX_UNITS_SYS_SAMPLES ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hApplet ; 

__attribute__((used)) static VOID
InitUnitsSysCB(HWND hwndDlg,
               PGLOBALDATA pGlobalData)
{
    WCHAR szUnitName[128];
    INT nCBIndex;

    /* Clear all box content */
    SendDlgItemMessageW(hwndDlg, IDC_NUMBERSMEASSYS,
                        CB_RESETCONTENT,
                        (WPARAM)0,
                        (LPARAM)0);

    /* Create list of standard system of units */
    for (nCBIndex = 0; nCBIndex < MAX_UNITS_SYS_SAMPLES; nCBIndex++)
    {
        LoadStringW(hApplet, IDS_METRIC + nCBIndex, szUnitName, 128);

        SendDlgItemMessageW(hwndDlg, IDC_NUMBERSMEASSYS,
                            CB_ADDSTRING,
                            0,
                            (LPARAM)szUnitName);
    }

    /* Set current item to value from registry */
    SendDlgItemMessageW(hwndDlg, IDC_NUMBERSMEASSYS,
                        CB_SETCURSEL,
                        (WPARAM)pGlobalData->nNumMeasure,
                        (LPARAM)0);
}