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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  char* DWORD ;

/* Variables and functions */
 int DELETE ; 
 int /*<<< orphan*/  DPRINT (char*,char*) ; 
 char* ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int KEY_ENUMERATE_SUB_KEYS ; 
 int KEY_QUERY_VALUE ; 
 int KEY_SET_VALUE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 char* RegDeleteTreeW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 char* ScmDeleteTree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swprintf (char*,char*,char*) ; 

__attribute__((used)) static
DWORD
ScmDeleteControlSet(
    DWORD dwControlSet)
{
    WCHAR szControlSetName[32];
    HKEY hControlSetKey = NULL;
    DWORD dwError;

    DPRINT("ScmDeleteControSet(%lu)\n", dwControlSet);

    /* Create the control set name */
    swprintf(szControlSetName, L"SYSTEM\\ControlSet%03lu", dwControlSet);
    DPRINT("Control set: %S\n", szControlSetName);

    /* Open the system key */
    dwError = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                            szControlSetName,
                            0,
                            DELETE | KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE | KEY_SET_VALUE,
                            &hControlSetKey);
    if (dwError != ERROR_SUCCESS)
        return dwError;

    /* Delete the control set */
#if (_WIN32_WINNT >= 0x0600)
    dwError = RegDeleteTreeW(hControlSetKey,
                             NULL);
#else
    dwError = ScmDeleteTree(hControlSetKey,
                            NULL);
#endif

    /* Open the system key */
    RegCloseKey(hControlSetKey);

    return dwError;
}