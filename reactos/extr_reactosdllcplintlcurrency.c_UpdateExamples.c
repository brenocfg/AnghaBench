#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_8__ {int /*<<< orphan*/  nInteger; } ;
struct TYPE_7__ {int /*<<< orphan*/  lpCurrencySymbol; int /*<<< orphan*/  PositiveOrder; int /*<<< orphan*/  NegativeOrder; int /*<<< orphan*/  lpThousandSep; int /*<<< orphan*/  lpDecimalSep; int /*<<< orphan*/  Grouping; int /*<<< orphan*/  LeadingZero; int /*<<< orphan*/  NumDigits; } ;
struct TYPE_6__ {size_t nCurrGrouping; int /*<<< orphan*/  UserLCID; int /*<<< orphan*/  szCurrSymbol; int /*<<< orphan*/  nCurrPosFormat; int /*<<< orphan*/  nCurrNegFormat; int /*<<< orphan*/  szCurrThousandSep; int /*<<< orphan*/  szCurrDecimalSep; int /*<<< orphan*/  nNumLeadingZero; int /*<<< orphan*/  nCurrDigits; } ;
typedef  TYPE_1__* PGLOBALDATA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_2__ CURRENCYFMTW ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrencyFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 TYPE_4__* GroupingFormats ; 
 int /*<<< orphan*/  IDC_CURRENCYNEGSAMPLE ; 
 int /*<<< orphan*/  IDC_CURRENCYPOSSAMPLE ; 
 int MAX_FMT_SIZE ; 
 int /*<<< orphan*/  NEGATIVE_EXAMPLE ; 
 int /*<<< orphan*/  POSITIVE_EXAMPLE ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 

__attribute__((used)) static VOID
UpdateExamples(HWND hwndDlg, PGLOBALDATA pGlobalData)
{
    WCHAR szBuffer[MAX_FMT_SIZE];
    CURRENCYFMTW CurrencyFormat;

    CurrencyFormat.NumDigits = pGlobalData->nCurrDigits;
    CurrencyFormat.LeadingZero = pGlobalData->nNumLeadingZero;
    CurrencyFormat.Grouping = GroupingFormats[pGlobalData->nCurrGrouping].nInteger;
    CurrencyFormat.lpDecimalSep = pGlobalData->szCurrDecimalSep;
    CurrencyFormat.lpThousandSep = pGlobalData->szCurrThousandSep;
    CurrencyFormat.NegativeOrder = pGlobalData->nCurrNegFormat;
    CurrencyFormat.PositiveOrder = pGlobalData->nCurrPosFormat;
    CurrencyFormat.lpCurrencySymbol = pGlobalData->szCurrSymbol;

    /* Positive example */
    GetCurrencyFormatW(pGlobalData->UserLCID, 0,
                       POSITIVE_EXAMPLE,
                       &CurrencyFormat, szBuffer, MAX_FMT_SIZE);

    SendDlgItemMessageW(hwndDlg, IDC_CURRENCYPOSSAMPLE, WM_SETTEXT, 0, (LPARAM)szBuffer);

    /* Negative example */
    GetCurrencyFormatW(pGlobalData->UserLCID, 0,
                       NEGATIVE_EXAMPLE,
                       &CurrencyFormat, szBuffer, MAX_FMT_SIZE);

    SendDlgItemMessageW(hwndDlg, IDC_CURRENCYNEGSAMPLE, WM_SETTEXT, 0, (LPARAM)szBuffer);
}