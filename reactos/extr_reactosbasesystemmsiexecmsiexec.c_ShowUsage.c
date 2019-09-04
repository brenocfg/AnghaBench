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
typedef  int /*<<< orphan*/  msiexec_version ;
typedef  int /*<<< orphan*/  filename ;
typedef  scalar_t__ WCHAR ;
typedef  scalar_t__* LPWSTR ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ExitProcess (int) ; 
 int GetLastError () ; 
 int GetModuleFileNameW (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetUserDefaultLangID () ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int LoadStringW (int /*<<< orphan*/ ,int,scalar_t__*,int) ; 
 int MAX_PATH ; 
 int MsiGetFileVersionW (scalar_t__*,scalar_t__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MsiMessageBoxW (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINE_ERR (char*,int) ; 
 int /*<<< orphan*/  sprintfW (scalar_t__*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static void ShowUsage(int ExitCode)
{
    WCHAR msiexec_version[40];
    WCHAR filename[MAX_PATH];
    LPWSTR msi_res;
    LPWSTR msiexec_help;
    HMODULE hmsi = GetModuleHandleA("msi.dll");
    DWORD len;
    DWORD res;

    /* MsiGetFileVersion need the full path */
    *filename = 0;
    res = GetModuleFileNameW(hmsi, filename, sizeof(filename) / sizeof(filename[0]));
    if (!res)
        WINE_ERR("GetModuleFileName failed: %d\n", GetLastError());

    len = sizeof(msiexec_version) / sizeof(msiexec_version[0]);
    *msiexec_version = 0;
    res = MsiGetFileVersionW(filename, msiexec_version, &len, NULL, NULL);
    if (res)
        WINE_ERR("MsiGetFileVersion failed with %d\n", res);

    /* Return the length of the resource.
       No typo: The LPWSTR parameter must be a LPWSTR * for this mode */
    len = LoadStringW(hmsi, 10, (LPWSTR) &msi_res, 0);

    msi_res = HeapAlloc(GetProcessHeap(), 0, (len + 1) * sizeof(WCHAR));
    msiexec_help = HeapAlloc(GetProcessHeap(), 0, (len + 1) * sizeof(WCHAR) + sizeof(msiexec_version));
    if (msi_res && msiexec_help) {
        *msi_res = 0;
        LoadStringW(hmsi, 10, msi_res, len + 1);

        sprintfW(msiexec_help, msi_res, msiexec_version);
        MsiMessageBoxW(0, msiexec_help, NULL, 0, GetUserDefaultLangID(), 0);
    }
    HeapFree(GetProcessHeap(), 0, msi_res);
    HeapFree(GetProcessHeap(), 0, msiexec_help);
    ExitProcess(ExitCode);
}