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
typedef  int /*<<< orphan*/ * HKEY ;
typedef  char* DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ *) ; 
 char* ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 char* RegCopyTreeW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* RegCreateKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,char**) ; 
 int /*<<< orphan*/  RegFlushKey (int /*<<< orphan*/ *) ; 
 char* RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 char* ScmCopyTree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swprintf (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static
DWORD
ScmCopyControlSet(
    DWORD dwSourceControlSet,
    DWORD dwDestinationControlSet)
{
    WCHAR szSourceControlSetName[32];
    WCHAR szDestinationControlSetName[32];
    HKEY hSourceControlSetKey = NULL;
    HKEY hDestinationControlSetKey = NULL;
    DWORD dwDisposition;
    DWORD dwError;

    /* Create the source control set name */
    swprintf(szSourceControlSetName, L"SYSTEM\\ControlSet%03lu", dwSourceControlSet);
    DPRINT("Source control set: %S\n", szSourceControlSetName);

    /* Create the destination control set name */
    swprintf(szDestinationControlSetName, L"SYSTEM\\ControlSet%03lu", dwDestinationControlSet);
    DPRINT("Destination control set: %S\n", szDestinationControlSetName);

    /* Open the source control set key */
    dwError = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                            szSourceControlSetName,
                            0,
                            KEY_READ,
                            &hSourceControlSetKey);
    if (dwError != ERROR_SUCCESS)
        goto done;

    /* Create the destination control set key */
    dwError = RegCreateKeyExW(HKEY_LOCAL_MACHINE,
                              szDestinationControlSetName,
                              0,
                              NULL,
                              REG_OPTION_NON_VOLATILE,
                              KEY_WRITE,
                              NULL,
                              &hDestinationControlSetKey,
                              &dwDisposition);
    if (dwError != ERROR_SUCCESS)
        goto done;

    /* Copy the source control set to the destination control set */
#if (_WIN32_WINNT >= 0x0600)
    dwError = RegCopyTreeW(hSourceControlSetKey,
                           NULL,
                           hDestinationControlSetKey);
#else
    dwError = ScmCopyTree(hSourceControlSetKey,
                          hDestinationControlSetKey);
#endif
    if (dwError != ERROR_SUCCESS)
        goto done;

    RegFlushKey(hDestinationControlSetKey);

done:
    if (hDestinationControlSetKey != NULL)
        RegCloseKey(hDestinationControlSetKey);

    if (hSourceControlSetKey != NULL)
        RegCloseKey(hSourceControlSetKey);

    return dwError;
}