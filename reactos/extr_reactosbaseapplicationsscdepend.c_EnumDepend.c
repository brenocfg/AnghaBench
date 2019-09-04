#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ lpServiceName; scalar_t__ lpDisplayName; int /*<<< orphan*/  ServiceStatus; } ;
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  TYPE_1__* LPENUM_SERVICE_STATUS ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  EnumDependentServices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,scalar_t__*,scalar_t__*) ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * OpenSCManager (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenService (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrintServiceStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReportLastError () ; 
 int /*<<< orphan*/  SC_MANAGER_CONNECT ; 
 int /*<<< orphan*/  SERVICE_ENUMERATE_DEPENDENTS ; 
 int /*<<< orphan*/  SERVICE_STATE_ALL ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,...) ; 

BOOL EnumDepend(LPCTSTR ServiceName)
{
    SC_HANDLE hManager = NULL;
    SC_HANDLE hService = NULL;
    BOOL bResult = TRUE;
    DWORD BufferSize = 0;
    DWORD EntriesRead = 0;
    LPENUM_SERVICE_STATUS pBuffer = NULL;
    DWORD i;

    hManager = OpenSCManager(NULL,
                             NULL,
                             SC_MANAGER_CONNECT);
    if (hManager == NULL)
    {
        _tprintf(_T("[SC] OpenSCManager FAILED %lu:\n\n"), GetLastError());
        bResult = FALSE;
        goto done;
    }

    hService = OpenService(hManager, ServiceName, SERVICE_ENUMERATE_DEPENDENTS);
    if (hService == NULL)
    {
        _tprintf(_T("[SC] OpenService FAILED %lu:\n\n"), GetLastError());
        bResult = FALSE;
        goto done;
    }

    if (!EnumDependentServices(hService,
                               SERVICE_STATE_ALL,
                               NULL,
                               0,
                               &BufferSize,
                               &EntriesRead))
    {
        if (BufferSize == 0)
        {
            _tprintf(_T("[SC] EnumDependentServices FAILED %lu:\n\n"), GetLastError());
            bResult = FALSE;
            goto done;
        }
    }

    pBuffer = HeapAlloc(GetProcessHeap(), 0, BufferSize);
    if (pBuffer == NULL)
    {
        SetLastError(ERROR_OUTOFMEMORY);
        _tprintf(_T("[SC] HeapAlloc FAILED %lu:\n\n"), GetLastError());
        bResult = FALSE;
        goto done;
    }

    if (!EnumDependentServices(hService,
                               SERVICE_STATE_ALL,
                               pBuffer,
                               BufferSize,
                               &BufferSize,
                               &EntriesRead))
    {
        _tprintf(_T("[SC] EnumDependentServices FAILED %lu:\n\n"), GetLastError());
        bResult = FALSE;
        goto done;
    }

    _tprintf(_T("Enum: entriesRead = %lu\n"), EntriesRead);

    for (i = 0; i < EntriesRead; i++)
    {
        _tprintf(_T("\n"));
        _tprintf(_T("SERVICE_NAME: %s\n"), pBuffer[i].lpServiceName);
        _tprintf(_T("DISPLAY_NAME: %s\n"), pBuffer[i].lpDisplayName);
        PrintServiceStatus(&pBuffer[i].ServiceStatus);
    }

done:
    if (bResult == FALSE)
        ReportLastError();

    if (pBuffer != NULL)
        HeapFree(GetProcessHeap(), 0, pBuffer);

    if (hService)
        CloseServiceHandle(hService);

    if (hManager)
        CloseServiceHandle(hManager);

    return bResult;
}