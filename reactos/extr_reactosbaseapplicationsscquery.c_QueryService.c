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
typedef  int /*<<< orphan*/ * LPSERVICE_STATUS_PROCESS ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OpenSCManager (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenService (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ QueryServiceStatusEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  ReportLastError () ; 
 int /*<<< orphan*/  SC_MANAGER_CONNECT ; 
 int /*<<< orphan*/  SC_STATUS_PROCESS_INFO ; 
 int /*<<< orphan*/  SERVICE_QUERY_STATUS ; 

LPSERVICE_STATUS_PROCESS
QueryService(LPCTSTR ServiceName)
{
    SC_HANDLE hSCManager = NULL;
    LPSERVICE_STATUS_PROCESS pServiceInfo = NULL;
    SC_HANDLE hSc = NULL;
    DWORD BufSiz = 0;
    DWORD BytesNeeded = 0;
    DWORD Ret;

    hSCManager = OpenSCManager(NULL,
                               NULL,
                               SC_MANAGER_CONNECT);
    if (hSCManager == NULL)
    {
        ReportLastError();
        return NULL;
    }

    hSc = OpenService(hSCManager,
                      ServiceName,
                      SERVICE_QUERY_STATUS);
    if (hSc == NULL)
        goto fail;

    Ret = QueryServiceStatusEx(hSc,
                               SC_STATUS_PROCESS_INFO,
                               NULL,
                               BufSiz,
                               &BytesNeeded);
    if ((Ret != 0) || (GetLastError() != ERROR_INSUFFICIENT_BUFFER))
        goto fail;

    pServiceInfo = (LPSERVICE_STATUS_PROCESS)HeapAlloc(GetProcessHeap(),
                                                       0,
                                                       BytesNeeded);
    if (pServiceInfo == NULL)
        goto fail;

    if (!QueryServiceStatusEx(hSc,
                              SC_STATUS_PROCESS_INFO,
                              (LPBYTE)pServiceInfo,
                              BytesNeeded,
                              &BytesNeeded))
    {
        goto fail;
    }

    CloseServiceHandle(hSc);
    CloseServiceHandle(hSCManager);
    return pServiceInfo;

fail:
    ReportLastError();
    if (pServiceInfo) HeapFree(GetProcessHeap(), 0, pServiceInfo);
    if (hSc) CloseServiceHandle(hSc);
    if (hSCManager) CloseServiceHandle(hSCManager);
    return NULL;
}