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
typedef  scalar_t__ INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OpenSCManager (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenService (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PrintService (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * QueryService (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReportLastError () ; 
 int /*<<< orphan*/  SC_MANAGER_CONNECT ; 
 int SERVICE_QUERY_STATUS ; 
 int SERVICE_START ; 
 int /*<<< orphan*/  StartService (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,...) ; 

BOOL Start(LPCTSTR ServiceName, LPCTSTR *ServiceArgs, INT ArgCount)
{
    SC_HANDLE hSCManager = NULL;
    SC_HANDLE hSc = NULL;
    LPSERVICE_STATUS_PROCESS pServiceInfo = NULL;
    BOOL bResult = TRUE;

#ifdef SCDBG
    LPCTSTR *TmpArgs = ServiceArgs;
    INT TmpCnt = ArgCount;
    _tprintf(_T("service to control - %s\n"), ServiceName);
    _tprintf(_T("Arguments:\n"));
    while (TmpCnt)
    {
        _tprintf(_T("  %s\n"), *TmpArgs);
        TmpArgs++;
        TmpCnt--;
    }
    _tprintf(_T("\n"));
#endif /* SCDBG */

    hSCManager = OpenSCManager(NULL,
                               NULL,
                               SC_MANAGER_CONNECT);
    if (hSCManager == NULL)
    {
        _tprintf(_T("[SC] OpenSCManager FAILED %lu:\n\n"), GetLastError());
        bResult = FALSE;
        goto done;
    }

    hSc = OpenService(hSCManager,
                      ServiceName,
                      SERVICE_START | SERVICE_QUERY_STATUS);
    if (hSc == NULL)
    {
        _tprintf(_T("[SC] OpenService FAILED %lu:\n\n"), GetLastError());
        bResult = FALSE;
        goto done;
    }

    if (!ArgCount)
    {
        ServiceArgs = NULL;
    }

    if (!StartService(hSc,
                      ArgCount,
                      ServiceArgs))
    {
        _tprintf(_T("[SC] StartService FAILED %lu:\n\n"), GetLastError());
        bResult = FALSE;
        goto done;
    }

    pServiceInfo = QueryService(ServiceName);
    if (pServiceInfo != NULL)
    {
        PrintService(ServiceName,
                     NULL,
                     pServiceInfo,
                     TRUE);

        HeapFree(GetProcessHeap(), 0, pServiceInfo);
    }

done:
    if (bResult == FALSE)
        ReportLastError();

    if (hSc)
        CloseServiceHandle(hSc);

    if (hSCManager)
        CloseServiceHandle(hSCManager);

    return bResult;
}