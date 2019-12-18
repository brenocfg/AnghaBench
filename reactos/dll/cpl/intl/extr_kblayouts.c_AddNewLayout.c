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
typedef  int WCHAR ;
typedef  scalar_t__ PWSTR ;
typedef  int /*<<< orphan*/  Lang ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  LCID ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CCH_LAYOUT_ID ; 
 int /*<<< orphan*/  CCH_ULONG_DEC ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int GetLayoutCount (int*) ; 
 int /*<<< orphan*/  GetLocaleInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 scalar_t__ IsLayoutExists (scalar_t__,int*) ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  LOCALE_ILANGUAGE ; 
 int /*<<< orphan*/  MAKELCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryInfoKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueExW (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ultow (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  lstrcpy (scalar_t__,int*) ; 
 scalar_t__ wcscmp (int*,scalar_t__) ; 
 scalar_t__ wcslen (int*) ; 
 int /*<<< orphan*/  wcstoul (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wsprintf (int*,char*,...) ; 

__attribute__((used)) static BOOL
AddNewLayout(PWSTR szLayoutID, PWSTR szLangID)
{
    WCHAR NewLayout[CCH_ULONG_DEC + 1], Lang[MAX_PATH],
          LangID[CCH_LAYOUT_ID + 1], SubPath[CCH_LAYOUT_ID + 1];
    HKEY hKey, hSubKey;
    DWORD cValues;
    LCID lcid;

    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Keyboard Layout\\Preload", 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
    {
        if (RegQueryInfoKey(hKey, NULL, NULL, NULL, NULL, NULL, NULL, &cValues, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
        {
            _ultow(cValues + 1, NewLayout, 10);

            lcid = wcstoul(szLangID, NULL, 16);

            GetLocaleInfoW(MAKELCID(lcid, SORT_DEFAULT), LOCALE_ILANGUAGE, Lang, sizeof(Lang) / sizeof(WCHAR));
            wsprintf(LangID, L"0000%s", Lang);

            if (IsLayoutExists(szLayoutID, LangID))
            {
                RegCloseKey(hKey);
                return FALSE;
            }

            if (GetLayoutCount(Lang) >= 1)
            {
                wsprintf(SubPath, L"d%03d%s", GetLayoutCount(Lang), Lang);
            }
            else if ((wcscmp(LangID, szLayoutID) != 0) && (GetLayoutCount(Lang) == 0))
            {
                wsprintf(SubPath, L"d%03d%s", 0, Lang);
            }
            else SubPath[0] = L'\0';

            if (wcslen(SubPath) != 0)
            {
                if (RegCreateKeyExW(HKEY_CURRENT_USER, L"Keyboard Layout\\Substitutes", 0, NULL,
                                    REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
                                    NULL, &hSubKey, NULL) == ERROR_SUCCESS)
                {
                    if (RegSetValueExW(hSubKey, SubPath, 0, REG_SZ, (LPBYTE)szLayoutID,
                                       (DWORD)((CCH_LAYOUT_ID + 1) * sizeof(WCHAR))) != ERROR_SUCCESS)
                    {
                        RegCloseKey(hSubKey);
                        RegCloseKey(hKey);
                        return FALSE;
                    }
                    RegCloseKey(hSubKey);
                }
                lstrcpy(szLayoutID, SubPath);
            }

            RegSetValueExW(hKey,
                           NewLayout,
                           0,
                           REG_SZ,
                           (LPBYTE)szLayoutID,
                           (DWORD)((CCH_LAYOUT_ID + 1) * sizeof(WCHAR)));
        }
        RegCloseKey(hKey);
    }

    return TRUE;
}