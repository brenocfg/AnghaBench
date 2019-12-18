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
typedef  int /*<<< orphan*/  dwRefCount ;
typedef  char* PWSTR ;
typedef  scalar_t__* PDWORD ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,scalar_t__,...) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/ * HKEY_LOCAL_MACHINE ; 
 int KEY_QUERY_VALUE ; 
 int KEY_SET_VALUE ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  RegQueryValueExW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ RegSetValueExW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static
DWORD
IncrementRefCount(
    PWSTR pszSidString,
    PDWORD pdwRefCount)
{
    HKEY hProfilesKey = NULL, hProfileKey = NULL;
    DWORD dwRefCount = 0, dwLength, dwType;
    DWORD dwError;

    DPRINT1("IncrementRefCount(%S %p)\n",
            pszSidString, pdwRefCount);

    dwError = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                            L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\ProfileList",
                            0,
                            KEY_QUERY_VALUE,
                            &hProfilesKey);
    if (dwError != ERROR_SUCCESS)
    {
        DPRINT1("Error: %lu\n", dwError);
        goto done;
    }

    dwError = RegOpenKeyExW(hProfilesKey,
                            pszSidString,
                            0,
                            KEY_QUERY_VALUE | KEY_SET_VALUE,
                            &hProfileKey);
    if (dwError != ERROR_SUCCESS)
    {
        DPRINT1("Error: %lu\n", dwError);
        goto done;
    }

    /* Get the reference counter */
    dwLength = sizeof(dwRefCount);
    RegQueryValueExW(hProfileKey,
                     L"RefCount",
                     NULL,
                     &dwType,
                     (PBYTE)&dwRefCount,
                     &dwLength);

    dwRefCount++;

    dwLength = sizeof(dwRefCount);
    dwError = RegSetValueExW(hProfileKey,
                             L"RefCount",
                             0,
                             REG_DWORD,
                             (PBYTE)&dwRefCount,
                             dwLength);
    if (dwError != ERROR_SUCCESS)
    {
        DPRINT1("Error: %lu\n", dwError);
        goto done;
    }

    if (pdwRefCount != NULL)
        *pdwRefCount = dwRefCount;

done:
    if (hProfileKey != NULL)
        RegCloseKey(hProfileKey);

    if (hProfilesKey != NULL)
        RegCloseKey(hProfilesKey);

    return dwError;
}