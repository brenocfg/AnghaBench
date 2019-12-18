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
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegDeleteKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _T (char*) ; 

__attribute__((used)) static int
RemoveAssociation(LPTSTR extension)
{
    DWORD return_val;
    HKEY hKey;

    return_val = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Classes"), 0, KEY_ALL_ACCESS, &hKey);

    if (return_val != ERROR_SUCCESS)
        return -1;

    return_val = RegDeleteKey(hKey, extension);
    RegCloseKey(hKey);

    if (return_val != ERROR_SUCCESS)
        return -2;

    return 0;
}