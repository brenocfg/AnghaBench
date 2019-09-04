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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  PGLOBAL_DATA ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int FALSE ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  KEY_READ ; 
 scalar_t__ LoadEventLabel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumKeyEx (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _T (char*) ; 
 scalar_t__ _countof (int /*<<< orphan*/ *) ; 

BOOL
LoadEventLabels(PGLOBAL_DATA pGlobalData)
{
    HKEY hSubKey;
    DWORD dwCurKey;
    TCHAR szName[MAX_PATH];
    DWORD dwName;
    DWORD dwResult;
    DWORD dwCount;
    if (RegOpenKeyEx(HKEY_CURRENT_USER,
                     _T("AppEvents\\EventLabels"),
                     0,
                     KEY_READ,
                     &hSubKey) != ERROR_SUCCESS)
    {
        return FALSE;
    }

    dwCurKey = 0;
    dwCount = 0;
    do
    {
        dwName = _countof(szName);
        dwResult = RegEnumKeyEx(hSubKey,
                                dwCurKey,
                                szName,
                                &dwName,
                                NULL,
                                NULL,
                                NULL,
                                NULL);

        if (dwResult == ERROR_SUCCESS)
        {
            if (LoadEventLabel(pGlobalData, hSubKey, szName))
            {
                dwCount++;
            }
        }
        dwCurKey++;

    } while (dwResult == ERROR_SUCCESS);

    RegCloseKey(hSubKey);
    return (dwCount != 0);
}