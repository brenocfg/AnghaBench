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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  INFCONTEXT ;
typedef  scalar_t__ HINF ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (char*) ; 
 int /*<<< orphan*/  DWORDfromString (char*) ; 
 int /*<<< orphan*/  INF_STYLE_WIN4 ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_STR_LEN ; 
 int /*<<< orphan*/  SetupCloseInfFile (scalar_t__) ; 
 scalar_t__ SetupFindFirstLineW (scalar_t__,char*,char*,int /*<<< orphan*/ *) ; 
 int SetupGetFieldCount (int /*<<< orphan*/ *) ; 
 scalar_t__ SetupGetStringFieldW (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SetupOpenInfFileW (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StringCchPrintfW (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int wcslen (char*) ; 
 char* wcstok (char*,char*) ; 

__attribute__((used)) static DWORD
GetDefaultLayoutForLocale(DWORD dwLocaleId)
{
    DWORD dwResult = 0;
    HINF hIntlInf;

    hIntlInf = SetupOpenInfFileW(L"intl.inf", NULL, INF_STYLE_WIN4, NULL);
    if (hIntlInf != INVALID_HANDLE_VALUE)
    {
        WCHAR szLangID[MAX_STR_LEN];
        INFCONTEXT InfContext;

        StringCchPrintfW(szLangID, ARRAYSIZE(szLangID), L"%08X", dwLocaleId);

        if (SetupFindFirstLineW(hIntlInf, L"Locales", szLangID, &InfContext))
        {
            if (SetupGetFieldCount(&InfContext) >= 5)
            {
                WCHAR szField[MAX_STR_LEN];

                if (SetupGetStringFieldW(&InfContext, 5, szField, ARRAYSIZE(szField), NULL))
                {
                    if (wcslen(szField) == 13) // like 0409:00000409 (13 chars)
                    {
                        WCHAR *pszSeparator = L":";
                        WCHAR *pszToken;

                        pszToken = wcstok(szField, pszSeparator);
                        if (pszToken != NULL)
                            pszToken = wcstok(NULL, pszSeparator);

                        if (pszToken != NULL)
                        {
                            dwResult = DWORDfromString(pszToken);
                        }
                    }
                }
            }
        }

        SetupCloseInfFile(hIntlInf);
    }

    return dwResult;
}