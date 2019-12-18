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
typedef  int /*<<< orphan*/  (* PINSTALL_REACTOS ) (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/ * HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * LoadLibraryW (char*) ; 

__attribute__((used)) static
INT
RunInstallReactOS(INT argc, WCHAR* argv[])
{
    INT RetVal;
    HMODULE hDll;
    PINSTALL_REACTOS InstallReactOS;

    hDll = LoadLibraryW(L"syssetup.dll");
    if (hDll == NULL)
    {
        DPRINT("Failed to load 'syssetup.dll'!\n");
        return GetLastError();
    }
    DPRINT("Loaded 'syssetup.dll'!\n");

    /* Call the standard Windows-compatible export */
    InstallReactOS = (PINSTALL_REACTOS)GetProcAddress(hDll, "InstallWindowsNt");
    if (InstallReactOS == NULL)
    {
        RetVal = GetLastError();
        DPRINT("Failed to get address for 'InstallWindowsNt()'!\n");
    }
    else
    {
        RetVal = InstallReactOS(argc, argv);
    }

    FreeLibrary(hDll);
    return RetVal;
}