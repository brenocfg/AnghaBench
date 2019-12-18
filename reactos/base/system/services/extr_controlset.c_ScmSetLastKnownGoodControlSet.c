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
typedef  int /*<<< orphan*/  dwControlSet ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegFlushKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
DWORD
ScmSetLastKnownGoodControlSet(
    DWORD dwControlSet)
{
    HKEY hSelectKey;
    DWORD dwError;

    dwError = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                            L"System\\Select",
                            0,
                            KEY_WRITE,
                            &hSelectKey);
    if (dwError != ERROR_SUCCESS)
        return dwError;

    dwError = RegSetValueExW(hSelectKey,
                             L"LastKnownGood",
                             0,
                             REG_DWORD,
                             (LPBYTE)&dwControlSet,
                             sizeof(dwControlSet));

    RegFlushKey(hSelectKey);
    RegCloseKey(hSelectKey);

    return dwError;
}