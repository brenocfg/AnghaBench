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
typedef  scalar_t__* PDWORD ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static
DWORD
ScmGetControlSetValues(
    PDWORD pdwCurrentControlSet,
    PDWORD pdwDefaultControlSet,
    PDWORD pdwFailedControlSet,
    PDWORD pdwLastKnownGoodControlSet)
{
    HKEY hSelectKey;
    DWORD dwType;
    DWORD dwSize;
    DWORD dwError;

    DPRINT("ScmGetControlSetValues() called\n");

    dwError = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                            L"System\\Select",
                            0,
                            KEY_READ,
                            &hSelectKey);
    if (dwError != ERROR_SUCCESS)
        return dwError;

    dwSize = sizeof(DWORD);
    dwError = RegQueryValueExW(hSelectKey,
                               L"Current",
                               0,
                               &dwType,
                               (LPBYTE)pdwCurrentControlSet,
                               &dwSize);
    if (dwError != ERROR_SUCCESS)
    {
        *pdwCurrentControlSet = 0;
    }

    dwSize = sizeof(DWORD);
    dwError = RegQueryValueExW(hSelectKey,
                               L"Default",
                               0,
                               &dwType,
                               (LPBYTE)pdwDefaultControlSet,
                               &dwSize);
    if (dwError != ERROR_SUCCESS)
    {
        *pdwDefaultControlSet = 0;
    }

    dwSize = sizeof(DWORD);
    dwError = RegQueryValueExW(hSelectKey,
                               L"Failed",
                               0,
                               &dwType,
                               (LPBYTE)pdwFailedControlSet,
                               &dwSize);
    if (dwError != ERROR_SUCCESS)
    {
        *pdwFailedControlSet = 0;
    }

    dwSize = sizeof(DWORD);
    dwError = RegQueryValueExW(hSelectKey,
                               L"LastKnownGood",
                               0,
                               &dwType,
                               (LPBYTE)pdwLastKnownGoodControlSet,
                               &dwSize);
    if (dwError != ERROR_SUCCESS)
    {
        *pdwLastKnownGoodControlSet = 0;
    }

    RegCloseKey(hSelectKey);

    DPRINT("ControlSets:\n");
    DPRINT("Current: %lu\n", *pdwCurrentControlSet);
    DPRINT("Default: %lu\n", *pdwDefaultControlSet);
    DPRINT("Failed: %lu\n", *pdwFailedControlSet);
    DPRINT("LastKnownGood: %lu\n", *pdwLastKnownGoodControlSet);

    return dwError;
}