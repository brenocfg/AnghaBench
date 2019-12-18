#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ lpDescription; } ;
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  TYPE_1__* LPSERVICE_DESCRIPTION ;
typedef  scalar_t__ LPCTSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * OpenSCManager (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenService (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QueryServiceConfig2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  ReportLastError () ; 
 int /*<<< orphan*/  SC_MANAGER_CONNECT ; 
 int /*<<< orphan*/  SERVICE_CONFIG_DESCRIPTION ; 
 int /*<<< orphan*/  SERVICE_QUERY_CONFIG ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 scalar_t__ _T (char*) ; 
 int /*<<< orphan*/  _tprintf (scalar_t__,...) ; 

BOOL QueryDescription(LPCTSTR ServiceName)
{
    SC_HANDLE hManager = NULL;
    SC_HANDLE hService = NULL;
    BOOL bResult = TRUE;
    DWORD cbBytesNeeded = 0;
    LPSERVICE_DESCRIPTION pServiceDescription = NULL;

#ifdef SCDBG
    _tprintf(_T("service to show description - %s\n\n"), ServiceName);
#endif

    hManager = OpenSCManager(NULL,
                             NULL,
                             SC_MANAGER_CONNECT);
    if (hManager == NULL)
    {
        _tprintf(_T("[SC] OpenSCManager FAILED %lu:\n\n"), GetLastError());
        bResult = FALSE;
        goto done;
    }

    hService = OpenService(hManager, ServiceName, SERVICE_QUERY_CONFIG);
    if (hService == NULL)
    {
        _tprintf(_T("[SC] OpenService FAILED %lu:\n\n"), GetLastError());
        bResult = FALSE;
        goto done;
    }

    if (!QueryServiceConfig2(hService,
                             SERVICE_CONFIG_DESCRIPTION,
                             NULL,
                             0,
                             &cbBytesNeeded))
    {
        if (cbBytesNeeded == 0)
        {
            _tprintf(_T("[SC] QueryServiceConfig2 FAILED %lu:\n\n"), GetLastError());
            bResult = FALSE;
            goto done;
        }
    }

    pServiceDescription = HeapAlloc(GetProcessHeap(), 0, cbBytesNeeded);
    if (pServiceDescription == NULL)
    {
        SetLastError(ERROR_OUTOFMEMORY);
        _tprintf(_T("[SC] HeapAlloc FAILED %lu:\n\n"), GetLastError());
        bResult = FALSE;
        goto done;
    }

    if (!QueryServiceConfig2(hService,
                             SERVICE_CONFIG_DESCRIPTION,
                             (LPBYTE)pServiceDescription,
                             cbBytesNeeded,
                             &cbBytesNeeded))
    {
        _tprintf(_T("[SC] QueryServiceConfig2 FAILED %lu:\n\n"), GetLastError());
        bResult = FALSE;
        goto done;
    }

    _tprintf(_T("[SC] QueryServiceConfig2 SUCCESS\n\n"));

    _tprintf(_T("SERVICE_NAME: %s\n"), ServiceName);
    _tprintf(_T("        DESCRIPTION        : %s\n"),
             (pServiceDescription->lpDescription) ? pServiceDescription->lpDescription : _T(""));

done:
    if (bResult == FALSE)
        ReportLastError();

    if (pServiceDescription != NULL)
        HeapFree(GetProcessHeap(), 0, pServiceDescription);

    if (hService)
        CloseServiceHandle(hService);

    if (hManager)
        CloseServiceHandle(hManager);

    return bResult;
}