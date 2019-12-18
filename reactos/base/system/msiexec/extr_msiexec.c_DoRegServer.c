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
typedef  int /*<<< orphan*/  SC_HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateServiceW (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_SERVICE_EXISTS ; 
 int /*<<< orphan*/  GENERIC_ALL ; 
 scalar_t__ GetLastError () ; 
 int GetSystemDirectoryW (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  OpenSCManagerW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_MANAGER_CREATE_SERVICE ; 
 int /*<<< orphan*/  SERVICES_ACTIVE_DATABASEW ; 
 int /*<<< orphan*/  SERVICE_DEMAND_START ; 
 int /*<<< orphan*/  SERVICE_ERROR_NORMAL ; 
 int /*<<< orphan*/  SERVICE_WIN32_SHARE_PROCESS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static DWORD DoRegServer(void)
{
    static const WCHAR msiserverW[] = {'M','S','I','S','e','r','v','e','r',0};
    static const WCHAR msiexecW[] = {'\\','m','s','i','e','x','e','c',' ','/','V',0};
    SC_HANDLE scm, service;
    WCHAR path[MAX_PATH+12];
    DWORD len, ret = 0;

    if (!(scm = OpenSCManagerW(NULL, SERVICES_ACTIVE_DATABASEW, SC_MANAGER_CREATE_SERVICE)))
    {
        fprintf(stderr, "Failed to open the service control manager.\n");
        return 1;
    }
    len = GetSystemDirectoryW(path, MAX_PATH);
    lstrcpyW(path + len, msiexecW);
    if ((service = CreateServiceW(scm, msiserverW, msiserverW, GENERIC_ALL,
                                  SERVICE_WIN32_SHARE_PROCESS, SERVICE_DEMAND_START,
                                  SERVICE_ERROR_NORMAL, path, NULL, NULL, NULL, NULL, NULL)))
    {
        CloseServiceHandle(service);
    }
    else if (GetLastError() != ERROR_SERVICE_EXISTS)
    {
        fprintf(stderr, "Failed to create MSI service\n");
        ret = 1;
    }
    CloseServiceHandle(scm);
    return ret;
}