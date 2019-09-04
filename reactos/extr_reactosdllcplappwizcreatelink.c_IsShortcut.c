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
typedef  int /*<<< orphan*/  Value ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int FALSE ; 
 scalar_t__ REG_SZ ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ wcsicmp (int /*<<< orphan*/ *,char*) ; 

BOOL
IsShortcut(HKEY hKey)
{
    WCHAR Value[10];
    DWORD Size;
    DWORD Type;

    Size = sizeof(Value);
    if (RegQueryValueExW(hKey, L"IsShortcut", NULL, &Type, (LPBYTE)Value, &Size) != ERROR_SUCCESS)
        return FALSE;

    if (Type != REG_SZ)
        return FALSE;

    return (wcsicmp(Value, L"yes") == 0);
}