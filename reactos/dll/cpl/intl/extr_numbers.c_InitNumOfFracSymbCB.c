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
struct TYPE_3__ {scalar_t__ nNumDigits; } ;
typedef  TYPE_1__* PGLOBALDATA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CB_ADDSTRING ; 
 int /*<<< orphan*/  CB_RESETCONTENT ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  DECIMAL_RADIX ; 
 int /*<<< orphan*/  IDC_NUMBERSNDIGDEC ; 
 scalar_t__ MAX_FRAC_NUM_SAMPLES ; 
 int MAX_SAMPLES_STR_SIZE ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _itow (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
InitNumOfFracSymbCB(HWND hwndDlg, PGLOBALDATA pGlobalData)
{
    WCHAR szFracCount[MAX_SAMPLES_STR_SIZE];
    INT nCBIndex;

    /* Clear all box content */
    SendDlgItemMessageW(hwndDlg, IDC_NUMBERSNDIGDEC,
                        CB_RESETCONTENT,
                        (WPARAM)0,
                        (LPARAM)0);

    /* Create standard list of fractional symbols */
    for (nCBIndex = 0; nCBIndex < MAX_FRAC_NUM_SAMPLES; nCBIndex++)
    {
        /* Convert to wide char */
        _itow(nCBIndex, szFracCount, DECIMAL_RADIX);

        SendDlgItemMessageW(hwndDlg, IDC_NUMBERSNDIGDEC,
                            CB_ADDSTRING,
                            0,
                            (LPARAM)szFracCount);
    }

    /* Set current item to value from registry */
    SendDlgItemMessageW(hwndDlg, IDC_NUMBERSNDIGDEC,
                        CB_SETCURSEL,
                        (WPARAM)pGlobalData->nNumDigits,
                        (LPARAM)0);
}