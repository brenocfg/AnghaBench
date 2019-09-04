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
typedef  int /*<<< orphan*/  szDispName ;
typedef  size_t UINT ;
typedef  char TCHAR ;
typedef  int SIZE_T ;
typedef  scalar_t__ LPTSTR ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (char*) ; 
 int /*<<< orphan*/  CCH_LAYOUT_ID ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ ExpandEnvironmentStrings (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeLibrary (scalar_t__) ; 
 int /*<<< orphan*/  GetLayoutID (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 scalar_t__ LoadLibrary (char*) ; 
 scalar_t__ LoadString (scalar_t__,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  StringCchCopy (scalar_t__,int,char*) ; 
 int /*<<< orphan*/  StringCchPrintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int _tcslen (char*) ; 
 int /*<<< orphan*/  _ttoi (char*) ; 

__attribute__((used)) static BOOL
GetLayoutName(LPTSTR szLayoutNum, LPTSTR szName, SIZE_T NameLength)
{
    HKEY hKey;
    DWORD dwBufLen;
    TCHAR szBuf[MAX_PATH], szDispName[MAX_PATH], szIndex[MAX_PATH], szPath[MAX_PATH];
    TCHAR szLCID[CCH_LAYOUT_ID + 1];
    HANDLE hLib;
    UINT i, j, k;

    if (!GetLayoutID(szLayoutNum, szLCID, ARRAYSIZE(szLCID)))
        return FALSE;

    StringCchPrintf(szBuf, ARRAYSIZE(szBuf), _T("SYSTEM\\CurrentControlSet\\Control\\Keyboard Layouts\\%s"), szLCID);

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, (LPCTSTR)szBuf, 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
    {
        dwBufLen = sizeof(szDispName);

        if (RegQueryValueEx(hKey, _T("Layout Display Name"), NULL, NULL, (LPBYTE)szDispName, &dwBufLen) == ERROR_SUCCESS)
        {
            if (szDispName[0] == '@')
            {
                size_t len = _tcslen(szDispName);

                for (i = 0; i < len; i++)
                {
                    if ((szDispName[i] == ',') && (szDispName[i + 1] == '-'))
                    {
                        for (j = i + 2, k = 0; j < _tcslen(szDispName)+1; j++, k++)
                        {
                            szIndex[k] = szDispName[j];
                        }
                        szDispName[i - 1] = '\0';
                        break;
                    }
                    else szDispName[i] = szDispName[i + 1];
                }

                if (ExpandEnvironmentStrings(szDispName, szPath, ARRAYSIZE(szPath)))
                {
                    hLib = LoadLibrary(szPath);
                    if (hLib)
                    {
                        if (LoadString(hLib, _ttoi(szIndex), szPath, ARRAYSIZE(szPath)) != 0)
                        {
                            StringCchCopy(szName, NameLength, szPath);
                            RegCloseKey(hKey);
                            FreeLibrary(hLib);
                            return TRUE;
                        }
                        FreeLibrary(hLib);
                    }
                }
            }
        }

        dwBufLen = NameLength * sizeof(TCHAR);

        if (RegQueryValueEx(hKey, _T("Layout Text"), NULL, NULL, (LPBYTE)szName, &dwBufLen) == ERROR_SUCCESS)
        {
            RegCloseKey(hKey);
            return TRUE;
        }

        RegCloseKey(hKey);
    }

    return FALSE;
}