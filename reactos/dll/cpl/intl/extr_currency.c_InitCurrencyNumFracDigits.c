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
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  nCurrDigits; } ;
typedef  TYPE_1__* PGLOBALDATA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CB_ADDSTRING ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  IDC_CURRENCYDECNUM ; 
 int MAX_FMT_SIZE ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
InitCurrencyNumFracDigits(HWND hwndDlg, PGLOBALDATA pGlobalData)
{
    WCHAR szBuffer[MAX_FMT_SIZE];
    int i;

    /* Create standard list of fractional symbols */
    for (i = 0; i < 10; i++)
    {
        szBuffer[0] = L'0' + i;
        szBuffer[1] = 0;
        SendDlgItemMessageW(hwndDlg, IDC_CURRENCYDECNUM,
                            CB_ADDSTRING,
                            0,
                            (LPARAM)szBuffer);
    }

    SendDlgItemMessageW(hwndDlg, IDC_CURRENCYDECNUM,
                        CB_SETCURSEL,
                        pGlobalData->nCurrDigits,
                        0);
}