#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ lpDescription; } ;
typedef  TYPE_1__ SERVICE_DESCRIPTION ;
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  scalar_t__ LPTSTR ;
typedef  scalar_t__ LPCTSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ChangeServiceConfig2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/ * OpenSCManager (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenService (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReportLastError () ; 
 int /*<<< orphan*/  SC_MANAGER_CONNECT ; 
 int /*<<< orphan*/  SERVICE_CHANGE_CONFIG ; 
 int /*<<< orphan*/  SERVICE_CONFIG_DESCRIPTION ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,...) ; 

BOOL SetDescription(LPCTSTR ServiceName, LPCTSTR Description)
{
    SC_HANDLE hManager = NULL;
    SC_HANDLE hService = NULL;
    BOOL bResult = TRUE;
    SERVICE_DESCRIPTION ServiceDescription;

#ifdef SCDBG
    _tprintf(_T("service to set description - %s\n\n"), ServiceName);
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

    hService = OpenService(hManager, ServiceName, SERVICE_CHANGE_CONFIG);
    if (hService == NULL)
    {
        _tprintf(_T("[SC] OpenService FAILED %lu:\n\n"), GetLastError());
        bResult = FALSE;
        goto done;
    }

    ServiceDescription.lpDescription = (LPTSTR)Description;

    if (!ChangeServiceConfig2(hService,
                              SERVICE_CONFIG_DESCRIPTION,
                              (LPBYTE)&ServiceDescription))
    {
        _tprintf(_T("[SC] ChangeServiceConfig2 FAILED %lu:\n\n"), GetLastError());
        bResult = FALSE;
        goto done;
    }

    _tprintf(_T("[SC] ChangeServiceConfig2 SUCCESS\n\n"));

done:
    if (bResult == FALSE)
        ReportLastError();

    if (hService)
        CloseServiceHandle(hService);

    if (hManager)
        CloseServiceHandle(hManager);

    return bResult;
}