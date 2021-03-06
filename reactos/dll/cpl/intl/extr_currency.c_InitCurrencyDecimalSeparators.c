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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {scalar_t__ szCurrDecimalSep; } ;
typedef  TYPE_1__* PGLOBALDATA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CB_ADDSTRING ; 
 int /*<<< orphan*/  CB_LIMITTEXT ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  IDC_CURRENCYDECSEP ; 
 scalar_t__ MAX_CURRDECIMALSEP ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
InitCurrencyDecimalSeparators(HWND hwndDlg, PGLOBALDATA pGlobalData)
{
    /* Limit text length */
    SendDlgItemMessageW(hwndDlg, IDC_CURRENCYDECSEP,
                        CB_LIMITTEXT,
                        MAX_CURRDECIMALSEP - 1,
                        0);

    /* Decimal separator */
    SendDlgItemMessageW(hwndDlg, IDC_CURRENCYDECSEP,
                        CB_ADDSTRING,
                        0,
                        (LPARAM)pGlobalData->szCurrDecimalSep);

    SendDlgItemMessageW(hwndDlg, IDC_CURRENCYDECSEP,
                        CB_SETCURSEL,
                        0, /* Index */
                        0);
}