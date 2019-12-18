#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {char* szBindName; int /*<<< orphan*/ * pszBinding; } ;
typedef  TYPE_1__ NetCfgComponentItem ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/ * CoTaskMemAlloc (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  wcscat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ *,char*) ; 

HRESULT
ReadBindingString(
    NetCfgComponentItem *Item)
{
    WCHAR szBuffer[200];
    HKEY hKey;
    DWORD dwType, dwSize;

    if (Item == NULL || Item->szBindName == NULL)
        return S_OK;

    wcscpy(szBuffer, L"SYSTEM\\CurrentControlSet\\Services\\");
    wcscat(szBuffer, Item->szBindName);
    wcscat(szBuffer, L"\\Linkage");

    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, szBuffer, 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        dwSize = 0;
        RegQueryValueExW(hKey, L"Bind", NULL, &dwType, NULL, &dwSize);

        if (dwSize != 0)
        {
            Item->pszBinding = CoTaskMemAlloc(dwSize);
            if (Item->pszBinding == NULL)
                return E_OUTOFMEMORY;

            RegQueryValueExW(hKey, L"Bind", NULL, &dwType, (LPBYTE)Item->pszBinding, &dwSize);
        }

        RegCloseKey(hKey);
    }

    return S_OK;
}