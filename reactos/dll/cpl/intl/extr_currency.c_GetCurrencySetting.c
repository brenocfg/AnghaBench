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
typedef  int WCHAR ;
struct TYPE_3__ {void* nCurrDigits; void* nCurrNegFormat; void* nCurrPosFormat; int /*<<< orphan*/  szCurrThousandSep; int /*<<< orphan*/  szCurrDecimalSep; void* nCurrGrouping; int /*<<< orphan*/  szCurrSymbol; } ;
typedef  TYPE_1__* PGLOBALDATA ;
typedef  void* INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetSelectedComboBoxIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  GetSelectedComboBoxText (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  IDC_CURRENCYDECNUM ; 
 int /*<<< orphan*/  IDC_CURRENCYDECSEP ; 
 int /*<<< orphan*/  IDC_CURRENCYGRPNUM ; 
 int /*<<< orphan*/  IDC_CURRENCYGRPSEP ; 
 int /*<<< orphan*/  IDC_CURRENCYNEGVALUE ; 
 int /*<<< orphan*/  IDC_CURRENCYPOSVALUE ; 
 int /*<<< orphan*/  IDC_CURRENCYSYMBOL ; 
 int MAX_CURRDECIMALSEP ; 
 int MAX_CURRSYMBOL ; 
 int MAX_CURRTHOUSANDSEP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static
BOOL
GetCurrencySetting(
     HWND hwndDlg,
     PGLOBALDATA pGlobalData)
{
    WCHAR szCurrSymbol[MAX_CURRSYMBOL];
    WCHAR szCurrDecimalSep[MAX_CURRDECIMALSEP];
    WCHAR szCurrThousandSep[MAX_CURRTHOUSANDSEP];
    INT nCurrPosFormat;
    INT nCurrNegFormat;
    INT nCurrDigits;
    INT nCurrGrouping;

    /* Currency symbol */
    GetSelectedComboBoxText(hwndDlg,
                            IDC_CURRENCYSYMBOL,
                            szCurrSymbol,
                            MAX_CURRSYMBOL);

    if (szCurrSymbol[0] == L'\0')
    {
        /* TODO: Show error message */

        return FALSE;
    }

    /* Positive Amount */
    GetSelectedComboBoxIndex(hwndDlg,
                             IDC_CURRENCYPOSVALUE,
                             &nCurrPosFormat);

    /* Negative Amount */
    GetSelectedComboBoxIndex(hwndDlg,
                             IDC_CURRENCYNEGVALUE,
                             &nCurrNegFormat);

    /* Decimal separator */
    GetSelectedComboBoxText(hwndDlg,
                            IDC_CURRENCYDECSEP,
                            szCurrDecimalSep,
                            MAX_CURRDECIMALSEP);

    if (szCurrDecimalSep[0] == L'\0')
    {
        /* TODO: Show error message */

        return FALSE;
    }

    /* Number of fractional digits */
    GetSelectedComboBoxIndex(hwndDlg,
                             IDC_CURRENCYDECNUM,
                             &nCurrDigits);

    /* Grouping symbol */
    GetSelectedComboBoxText(hwndDlg,
                            IDC_CURRENCYGRPSEP,
                            szCurrThousandSep,
                            MAX_CURRTHOUSANDSEP);

    if (szCurrThousandSep[0] == L'\0')
    {
        /* TODO: Show error message */

        return FALSE;
    }

    /* Digit grouping */
    GetSelectedComboBoxIndex(hwndDlg,
                             IDC_CURRENCYGRPNUM,
                             &nCurrGrouping);

    /* Store settings in global data */
    wcscpy(pGlobalData->szCurrSymbol, szCurrSymbol);
    pGlobalData->nCurrGrouping = nCurrGrouping;
    wcscpy(pGlobalData->szCurrDecimalSep, szCurrDecimalSep);
    wcscpy(pGlobalData->szCurrThousandSep, szCurrThousandSep);
    pGlobalData->nCurrPosFormat = nCurrPosFormat;
    pGlobalData->nCurrNegFormat = nCurrNegFormat;
    pGlobalData->nCurrDigits = nCurrDigits;

    return TRUE;
}