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
typedef  int /*<<< orphan*/  szPreload ;
typedef  int /*<<< orphan*/  szLayoutID ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CCH_LAYOUT_ID ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumValue (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ wcscmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wcslen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static INT
GetLayoutCount(PWSTR szLang)
{
    HKEY hKey;
    WCHAR szLayoutID[3 + 1], szPreload[CCH_LAYOUT_ID + 1], szLOLang[MAX_PATH];
    DWORD dwIndex = 0, dwType, dwSize;
    UINT Count = 0, i, j;

    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Keyboard Layout\\Preload",
        0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
    {
        dwSize = sizeof(szLayoutID);

        while (RegEnumValue(hKey, dwIndex, szLayoutID, &dwSize, NULL, &dwType, NULL, NULL) == ERROR_SUCCESS)
        {
            dwSize = sizeof(szPreload);
            RegQueryValueExW(hKey, szLayoutID, NULL, NULL, (LPBYTE)szPreload, &dwSize);

            for (i = 4, j = 0; i < wcslen(szPreload)+1; i++, j++)
                szLOLang[j] = szPreload[i];

            if (wcscmp(szLOLang, szLang) == 0) Count += 1;

            dwSize = sizeof(szLayoutID);
            dwIndex++;
        }

        RegCloseKey(hKey);
    }

    return Count;
}