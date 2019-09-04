#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nf ;
typedef  int WCHAR ;
typedef  size_t UINT ;
struct TYPE_4__ {int* lpDecimalSep; int* lpThousandSep; int Grouping; } ;
typedef  TYPE_1__ NUMBERFMTW ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  char* LONGLONG ;
typedef  size_t INT ;

/* Variables and functions */
 size_t GetLocaleInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 size_t GetNumberFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  LOCALE_SDECIMAL ; 
 int /*<<< orphan*/  LOCALE_SGROUPING ; 
 int /*<<< orphan*/  LOCALE_STHOUSAND ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _countof (int*) ; 
 int /*<<< orphan*/  swprintf (int*,char*,char*) ; 

UINT
FormatInteger(LONGLONG Num, LPWSTR pwszResult, UINT cchResultMax)
{
    WCHAR wszNumber[24];
    WCHAR wszDecimalSep[8], wszThousandSep[8];
    NUMBERFMTW nf;
    WCHAR wszGrouping[12];
    INT cchGrouping;
    INT cchResult;
    INT i;

    // Print the number in uniform mode
    swprintf(wszNumber, L"%I64u", Num);

    // Get system strings for decimal and thousand separators.
    GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, wszDecimalSep, _countof(wszDecimalSep));
    GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_STHOUSAND, wszThousandSep, _countof(wszThousandSep));

    // Initialize format for printing the number in bytes
    ZeroMemory(&nf, sizeof(nf));
    nf.lpDecimalSep = wszDecimalSep;
    nf.lpThousandSep = wszThousandSep;

    // Get system string for groups separator
    cchGrouping = GetLocaleInfoW(LOCALE_USER_DEFAULT,
                                 LOCALE_SGROUPING,
                                 wszGrouping,
                                 _countof(wszGrouping));

    // Convert grouping specs from string to integer
    for (i = 0; i < cchGrouping; i++)
    {
        WCHAR wch = wszGrouping[i];

        if (wch >= L'0' && wch <= L'9')
            nf.Grouping = nf.Grouping * 10 + (wch - L'0');
        else if (wch != L';')
            break;
    }

    if ((nf.Grouping % 10) == 0)
        nf.Grouping /= 10;
    else
        nf.Grouping *= 10;

    // Format the number
    cchResult = GetNumberFormatW(LOCALE_USER_DEFAULT,
                                 0,
                                 wszNumber,
                                 &nf,
                                 pwszResult,
                                 cchResultMax);

    if (!cchResult)
        return 0;

    // GetNumberFormatW returns number of characters including UNICODE_NULL
    return cchResult - 1;
}