#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {int Grouping; int PositiveOrder; scalar_t__ NegativeOrder; int /*<<< orphan*/  lpCurrencySymbol; int /*<<< orphan*/  lpThousandSep; int /*<<< orphan*/  lpDecimalSep; scalar_t__ LeadingZero; int /*<<< orphan*/  NumDigits; } ;
struct TYPE_5__ {int nCurrPosFormat; int /*<<< orphan*/  UserLCID; int /*<<< orphan*/  szCurrSymbol; int /*<<< orphan*/  szCurrThousandSep; int /*<<< orphan*/  szCurrDecimalSep; int /*<<< orphan*/  nCurrDigits; } ;
typedef  TYPE_1__* PGLOBALDATA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_2__ CURRENCYFMTW ;

/* Variables and functions */
 int /*<<< orphan*/  CB_INSERTSTRING ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  GetCurrencyFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IDC_CURRENCYPOSVALUE ; 
 int MAX_FMT_SIZE ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
InitCurrencyPositiveFormats(HWND hwndDlg, PGLOBALDATA pGlobalData)
{
    WCHAR szBuffer[MAX_FMT_SIZE];
    CURRENCYFMTW cyFmt;
    INT i;

    /* positive currency values */
    cyFmt.NumDigits = pGlobalData->nCurrDigits;
    cyFmt.LeadingZero = 0;
    cyFmt.Grouping = 3;
    cyFmt.lpDecimalSep = pGlobalData->szCurrDecimalSep;
    cyFmt.lpThousandSep = pGlobalData->szCurrThousandSep;
    cyFmt.lpCurrencySymbol = pGlobalData->szCurrSymbol;
    cyFmt.NegativeOrder = 0;

    for (i = 0; i < 4; i++)
    {
        cyFmt.PositiveOrder = i;
        GetCurrencyFormatW(pGlobalData->UserLCID, 0,
                           L"1.1",
                           &cyFmt, szBuffer, MAX_FMT_SIZE);

        SendDlgItemMessageW(hwndDlg, IDC_CURRENCYPOSVALUE,
                            CB_INSERTSTRING,
                            -1,
                            (LPARAM)szBuffer);
    }

    SendDlgItemMessageW(hwndDlg, IDC_CURRENCYPOSVALUE,
                        CB_SETCURSEL,
                        pGlobalData->nCurrPosFormat,
                        0);
}