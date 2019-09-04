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
typedef  int /*<<< orphan*/  REGSAM ;
typedef  int /*<<< orphan*/ ** PHKEY ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/ * HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

DWORD
ScmOpenServiceKey(LPWSTR lpServiceName,
                  REGSAM samDesired,
                  PHKEY phKey)
{
    HKEY hServicesKey = NULL;
    DWORD dwError;

    *phKey = NULL;

    dwError = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                            L"System\\CurrentControlSet\\Services",
                            0,
                            KEY_READ,
                            &hServicesKey);
    if (dwError != ERROR_SUCCESS)
        return dwError;

    dwError = RegOpenKeyExW(hServicesKey,
                            lpServiceName,
                            0,
                            samDesired,
                            phKey);

    RegCloseKey(hServicesKey);

    return dwError;
}