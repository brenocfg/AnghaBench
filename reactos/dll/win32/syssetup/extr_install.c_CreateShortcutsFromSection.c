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
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  INFCONTEXT ;
typedef  int /*<<< orphan*/  HINF ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int*) ; 
 int /*<<< orphan*/  CreateShortcut (int /*<<< orphan*/ ,int*,int*,int*,int,int*) ; 
 int /*<<< orphan*/  FALSE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetupFindFirstLine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SetupFindNextLine (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SetupGetFieldCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupGetIntField (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  SetupGetStringFieldW (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wcscat (int*,char*) ; 

__attribute__((used)) static BOOL CreateShortcutsFromSection(HINF hinf, LPWSTR pszSection, LPCWSTR pszFolder)
{
    INFCONTEXT Context;
    DWORD dwFieldCount;
    INT iIconNr;
    WCHAR szCommand[MAX_PATH];
    WCHAR szName[MAX_PATH];
    WCHAR szDescription[MAX_PATH];
    WCHAR szDirectory[MAX_PATH];

    if (!SetupFindFirstLine(hinf, pszSection, NULL, &Context))
        return FALSE;

    do
    {
        dwFieldCount = SetupGetFieldCount(&Context);
        if (dwFieldCount < 3)
            continue;

        if (!SetupGetStringFieldW(&Context, 1, szCommand, ARRAYSIZE(szCommand), NULL))
            continue;

        if (!SetupGetStringFieldW(&Context, 2, szName, ARRAYSIZE(szName), NULL))
            continue;

        if (!SetupGetStringFieldW(&Context, 3, szDescription, ARRAYSIZE(szDescription), NULL))
            continue;

        if (dwFieldCount < 4 || !SetupGetIntField(&Context, 4, &iIconNr))
            iIconNr = -1; /* Special value to indicate no icon */

        if (dwFieldCount < 5 || !SetupGetStringFieldW(&Context, 5, szDirectory, ARRAYSIZE(szDirectory), NULL))
            szDirectory[0] = L'\0';

        wcscat(szName, L".lnk");

        CreateShortcut(pszFolder, szName, szCommand, szDescription, iIconNr, szDirectory);

    } while (SetupFindNextLine(&Context, &Context));

    return TRUE;
}