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
 int /*<<< orphan*/  DELETE ; 
 int /*<<< orphan*/  DeleteService (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_SERVICE_DOES_NOT_EXIST ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  OpenSCManagerW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenServiceW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_MANAGER_CONNECT ; 
 int /*<<< orphan*/  SERVICES_ACTIVE_DATABASEW ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static DWORD DoUnregServer(void)
{
    static const WCHAR msiserverW[] = {'M','S','I','S','e','r','v','e','r',0};
    SC_HANDLE scm, service;
    DWORD ret = 0;

    if (!(scm = OpenSCManagerW(NULL, SERVICES_ACTIVE_DATABASEW, SC_MANAGER_CONNECT)))
    {
        fprintf(stderr, "Failed to open service control manager\n");
        return 1;
    }
    if ((service = OpenServiceW(scm, msiserverW, DELETE)))
    {
        if (!DeleteService(service))
        {
            fprintf(stderr, "Failed to delete MSI service\n");
            ret = 1;
        }
        CloseServiceHandle(service);
    }
    else if (GetLastError() != ERROR_SERVICE_DOES_NOT_EXIST)
    {
        fprintf(stderr, "Failed to open MSI service\n");
        ret = 1;
    }
    CloseServiceHandle(scm);
    return ret;
}