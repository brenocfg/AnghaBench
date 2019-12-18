#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int WCHAR ;
typedef  size_t UINT ;
typedef  int* PWSTR ;
typedef  int* LPWSTR ;
typedef  int* LPTSTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MAX_SAMPLES_STR_SIZE ; 
 int /*<<< orphan*/  STD_DATE_SEP ; 
 int /*<<< orphan*/  isDateCompAl (int const) ; 
 int /*<<< orphan*/  wcscpy (int*,int /*<<< orphan*/ ) ; 
 size_t wcslen (int const*) ; 

LPTSTR
FindDateSep(const WCHAR *szSourceStr)
{
    PWSTR pszFoundSep;
    UINT nDateCompCount=0;
    UINT nDateSepCount=0;

    pszFoundSep = (LPWSTR)HeapAlloc(GetProcessHeap(), 0, MAX_SAMPLES_STR_SIZE * sizeof(WCHAR));
    if (pszFoundSep == NULL)
        return NULL;

    wcscpy(pszFoundSep,STD_DATE_SEP);

    while (nDateCompCount < wcslen(szSourceStr))
    {
        if (!isDateCompAl(szSourceStr[nDateCompCount]) && (szSourceStr[nDateCompCount] != L'\''))
        {
            while (!isDateCompAl(szSourceStr[nDateCompCount]) && (szSourceStr[nDateCompCount] != L'\''))
            {
                pszFoundSep[nDateSepCount++] = szSourceStr[nDateCompCount];
                nDateCompCount++;
            }

            pszFoundSep[nDateSepCount] = L'\0';
            return pszFoundSep;
        }

        nDateCompCount++;
    }

    return pszFoundSep;
}