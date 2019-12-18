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
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  ENUM_SERVICE_STATUS_PROCESS ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ EnumServicesStatusEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OpenSCManager (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReportLastError () ; 
 int /*<<< orphan*/  SC_ENUM_PROCESS_INFO ; 
 int /*<<< orphan*/  SC_MANAGER_ENUMERATE_SERVICE ; 

__attribute__((used)) static
DWORD
EnumServices(ENUM_SERVICE_STATUS_PROCESS **pServiceStatus,
             DWORD dwServiceType,
             DWORD dwServiceState,
             DWORD dwBufferSize,
             DWORD dwResumeIndex,
             LPCTSTR pszGroupName)
{
    SC_HANDLE hSCManager;
    DWORD BytesNeeded = 0;
    DWORD ResumeHandle = dwResumeIndex;
    DWORD NumServices = 0;
    BOOL Ret;

    hSCManager = OpenSCManager(NULL,
                               NULL,
                               SC_MANAGER_ENUMERATE_SERVICE);
    if (hSCManager == NULL)
    {
        ReportLastError();
        return 0;
    }

    if (dwBufferSize == 0)
    {
        Ret = EnumServicesStatusEx(hSCManager,
                                   SC_ENUM_PROCESS_INFO,
                                   dwServiceType,
                                   dwServiceState,
                                   (LPBYTE)*pServiceStatus,
                                   dwBufferSize,
                                   &BytesNeeded,
                                   &NumServices,
                                   &ResumeHandle,
                                   pszGroupName);
        if ((Ret == 0) && (GetLastError() != ERROR_MORE_DATA))
        {
            ReportLastError();
            return 0;
        }

        dwBufferSize = BytesNeeded;
    }

    *pServiceStatus = (ENUM_SERVICE_STATUS_PROCESS *)
                      HeapAlloc(GetProcessHeap(),
                                0,
                                dwBufferSize);
    if (*pServiceStatus != NULL)
    {
        if (EnumServicesStatusEx(hSCManager,
                                 SC_ENUM_PROCESS_INFO,
                                 dwServiceType,
                                 dwServiceState,
                                 (LPBYTE)*pServiceStatus,
                                 dwBufferSize,
                                 &BytesNeeded,
                                 &NumServices,
                                 &ResumeHandle,
                                 pszGroupName))
        {
            CloseServiceHandle(hSCManager);
            return NumServices;
        }
    }

    ReportLastError();
    if (*pServiceStatus)
        HeapFree(GetProcessHeap(), 0, *pServiceStatus);

    CloseServiceHandle(hSCManager);

    return NumServices;
}