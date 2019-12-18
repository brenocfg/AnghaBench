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
struct TYPE_7__ {char* lpDecimalSep; char* lpCurrencySymbol; int /*<<< orphan*/  Grouping; scalar_t__ NegativeOrder; scalar_t__ PositiveOrder; int /*<<< orphan*/  lpThousandSep; scalar_t__ LeadingZero; scalar_t__ NumDigits; } ;
struct TYPE_6__ {int nCurrGrouping; int /*<<< orphan*/  UserLCID; int /*<<< orphan*/  szCurrThousandSep; } ;
typedef  TYPE_1__* PGLOBALDATA ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_2__ CURRENCYFMTW ;

/* Variables and functions */
 int /*<<< orphan*/  CB_INSERTSTRING ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  GetCurrencyFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 TYPE_4__* GroupingFormats ; 
 int /*<<< orphan*/  IDC_CURRENCYGRPNUM ; 
 int MAX_FMT_SIZE ; 
 size_t MAX_GROUPINGFORMATS ; 
 int /*<<< orphan*/  SendDlgItemMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
InitDigitGroupCB(HWND hwndDlg, PGLOBALDATA pGlobalData)
{
    WCHAR szBuffer[MAX_FMT_SIZE];
    CURRENCYFMTW cyFmt;
    INT i;

    /* Digit grouping */
    cyFmt.NumDigits = 0;
    cyFmt.LeadingZero = 0;
    cyFmt.lpDecimalSep = L"";
    cyFmt.lpThousandSep = pGlobalData->szCurrThousandSep;
    cyFmt.PositiveOrder = 0;
    cyFmt.NegativeOrder = 0;
    cyFmt.lpCurrencySymbol = L"";

    for (i = 0 ; i < MAX_GROUPINGFORMATS ; i++)
    {
       cyFmt.Grouping = GroupingFormats[i].nInteger;

       GetCurrencyFormatW(pGlobalData->UserLCID, 0,
                          L"123456789",
                          &cyFmt, szBuffer, MAX_FMT_SIZE);
       SendDlgItemMessageW(hwndDlg, IDC_CURRENCYGRPNUM,
                           CB_INSERTSTRING,
                           -1,
                           (LPARAM)szBuffer);
    }

    SendDlgItemMessageW(hwndDlg, IDC_CURRENCYGRPNUM,
                        CB_SETCURSEL,
                        pGlobalData->nCurrGrouping,
                        0);
}