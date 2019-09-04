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
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 

BOOL
ScmIsDeleteFlagSet(HKEY hServiceKey)
{
    DWORD dwError;
    DWORD dwType;
    DWORD dwFlag;
    DWORD dwSize = sizeof(DWORD);

    dwError = RegQueryValueExW(hServiceKey,
                               L"DeleteFlag",
                               0,
                               &dwType,
                               (LPBYTE)&dwFlag,
                               &dwSize);

    return (dwError == ERROR_SUCCESS);
}