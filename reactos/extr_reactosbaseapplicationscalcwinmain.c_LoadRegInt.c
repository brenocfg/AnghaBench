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
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int LoadRegInt(LPCTSTR lpszApp, LPCTSTR lpszKey, int iDefault)
{
    HKEY  hKey;
    int   iValue;
    DWORD tmp;

    if (RegOpenKeyEx(HKEY_CURRENT_USER, lpszApp, 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
    {
        /* Try to load integer value */
        tmp = sizeof(int);

        if (RegQueryValueEx(hKey, lpszKey, NULL, NULL, (LPBYTE)&iValue, &tmp) == ERROR_SUCCESS)
            iDefault = iValue;

        /* close the key */
        RegCloseKey(hKey);
    }

    return iDefault;
}