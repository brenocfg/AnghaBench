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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  INFCONTEXT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * HMODULE ;
typedef  int /*<<< orphan*/  HINF ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CSIDL_SYSTEM ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FatalError (char*,...) ; 
 int /*<<< orphan*/ * LoadLibraryW (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  PathAddBackslash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHGetFolderPathW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupFindFirstLine (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SetupFindNextLine (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupGetIntField (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupGetStringFieldW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  __wine_register_resources (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

BOOL
RegisterTypeLibraries(HINF hinf, LPCWSTR szSection)
{
    INFCONTEXT InfContext;
    BOOL res;
    WCHAR szName[MAX_PATH];
    WCHAR szPath[MAX_PATH];
    INT csidl;
    LPWSTR p;
    HMODULE hmod;
    HRESULT hret;

    /* Begin iterating the entries in the inf section */
    res = SetupFindFirstLine(hinf, szSection, NULL, &InfContext);
    if (!res) return FALSE;

    do
    {
        /* Get the name of the current type library */
        if (!SetupGetStringFieldW(&InfContext, 1, szName, ARRAYSIZE(szName), NULL))
        {
            FatalError("SetupGetStringFieldW failed\n");
            continue;
        }

        if (!SetupGetIntField(&InfContext, 2, &csidl))
            csidl = CSIDL_SYSTEM;

        hret = SHGetFolderPathW(NULL, csidl, NULL, 0, szPath);
        if (FAILED(hret))
        {
            FatalError("SHGetFolderPathW failed hret=0x%lx\n", hret);
            continue;
        }

        p = PathAddBackslash(szPath);
        wcscpy(p, szName);

        hmod = LoadLibraryW(szName);
        if (hmod == NULL)
        {
            FatalError("LoadLibraryW failed\n");
            continue;
        }

        __wine_register_resources(hmod);

    } while (SetupFindNextLine(&InfContext, &InfContext));

    return TRUE;
}