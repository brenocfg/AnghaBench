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
typedef  scalar_t__ LPTSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int INT ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegCreateKeyEx (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ RegSetValueEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int _tcslen (scalar_t__) ; 

__attribute__((used)) static INT
AddAssociation(LPTSTR extension, LPTSTR type)
{
    DWORD return_val;
    HKEY hKey = NULL, insideKey = NULL;

    return_val = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Classes"), 0, KEY_ALL_ACCESS, &hKey);

    if (return_val != ERROR_SUCCESS)
        return -1;

    return_val = RegCreateKeyEx(hKey, extension, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &insideKey, NULL);
    RegCloseKey(hKey);

    if (return_val != ERROR_SUCCESS)
        return -1;

    return_val = RegSetValueEx(insideKey, NULL, 0, REG_SZ, (LPBYTE)type, (_tcslen(type) + 1) * sizeof(TCHAR));
    RegCloseKey(insideKey);

    if (return_val != ERROR_SUCCESS)
        return -2;

    return 0;
}