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
struct TYPE_3__ {scalar_t__ szCurrThousandSep; } ;
typedef  TYPE_1__* PGLOBALDATA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CB_ADDSTRING ; 
 int /*<<< orphan*/  CB_LIMITTEXT ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  IDC_CURRENCYGRPSEP ; 
 scalar_t__ MAX_CURRTHOUSANDSEP ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
InitCurrencyGroupSeparators(HWND hwndDlg, PGLOBALDATA pGlobalData)
{
    /* Limit text length */
    SendDlgItemMessageW(hwndDlg, IDC_CURRENCYGRPSEP,
                        CB_LIMITTEXT,
                        MAX_CURRTHOUSANDSEP - 1,
                        0);

    /* Digit group separator */
    SendDlgItemMessageW(hwndDlg, IDC_CURRENCYGRPSEP,
                        CB_ADDSTRING,
                        0,
                        (LPARAM)pGlobalData->szCurrThousandSep);

    SendDlgItemMessageW(hwndDlg, IDC_CURRENCYGRPSEP,
                        CB_SETCURSEL,
                        0, /* Index */
                        0);
}