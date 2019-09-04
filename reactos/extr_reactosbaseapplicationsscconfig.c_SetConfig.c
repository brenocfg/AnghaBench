#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lpDisplayName; int /*<<< orphan*/  lpPassword; int /*<<< orphan*/  lpServiceStartName; int /*<<< orphan*/  lpDependencies; int /*<<< orphan*/  dwTagId; scalar_t__ bTagId; int /*<<< orphan*/  lpLoadOrderGroup; int /*<<< orphan*/  lpBinaryPathName; int /*<<< orphan*/  dwErrorControl; int /*<<< orphan*/  dwStartType; int /*<<< orphan*/  dwServiceType; int /*<<< orphan*/  lpServiceName; } ;
typedef  TYPE_1__ SERVICE_CREATE_INFO ;
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ChangeServiceConfig (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/ * OpenSCManager (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenService (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ParseCreateConfigArguments (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  ReportLastError () ; 
 int /*<<< orphan*/  SC_MANAGER_CONNECT ; 
 int /*<<< orphan*/  SERVICE_CHANGE_CONFIG ; 
 int /*<<< orphan*/  SetConfigUsage () ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,...) ; 

BOOL SetConfig(LPCTSTR *ServiceArgs, INT ArgCount)
{
    SC_HANDLE hManager = NULL;
    SC_HANDLE hService = NULL;
    BOOL bResult = TRUE;
    SERVICE_CREATE_INFO ServiceInfo;

    if (!ParseCreateConfigArguments(ServiceArgs, ArgCount, TRUE, &ServiceInfo))
    {
        SetConfigUsage();
        return FALSE;
    }

#ifdef SCDBG
    _tprintf(_T("service name - %s\n"), ServiceInfo.lpServiceName);
    _tprintf(_T("display name - %s\n"), ServiceInfo.lpDisplayName);
    _tprintf(_T("service type - %lu\n"), ServiceInfo.dwServiceType);
    _tprintf(_T("start type - %lu\n"), ServiceInfo.dwStartType);
    _tprintf(_T("error control - %lu\n"), ServiceInfo.dwErrorControl);
    _tprintf(_T("Binary path - %s\n"), ServiceInfo.lpBinaryPathName);
    _tprintf(_T("load order group - %s\n"), ServiceInfo.lpLoadOrderGroup);
    _tprintf(_T("tag - %lu\n"), ServiceInfo.dwTagId);
    _tprintf(_T("dependencies - %s\n"), ServiceInfo.lpDependencies);
    _tprintf(_T("account start name - %s\n"), ServiceInfo.lpServiceStartName);
    _tprintf(_T("account password - %s\n"), ServiceInfo.lpPassword);
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

    hService = OpenService(hManager,
                           ServiceInfo.lpServiceName,
                           SERVICE_CHANGE_CONFIG);
    if (hService == NULL)
    {
        _tprintf(_T("[SC] OpenService FAILED %lu:\n\n"), GetLastError());
        bResult = FALSE;
        goto done;
    }

    if (!ChangeServiceConfig(hService,
                             ServiceInfo.dwServiceType,
                             ServiceInfo.dwStartType,
                             ServiceInfo.dwErrorControl,
                             ServiceInfo.lpBinaryPathName,
                             ServiceInfo.lpLoadOrderGroup,
                             ServiceInfo.bTagId ? &ServiceInfo.dwTagId : NULL,
                             ServiceInfo.lpDependencies,
                             ServiceInfo.lpServiceStartName,
                             ServiceInfo.lpPassword,
                             ServiceInfo.lpDisplayName))
    {
        _tprintf(_T("[SC] ChangeServiceConfig FAILED %lu:\n\n"), GetLastError());
        bResult = FALSE;
        goto done;
    }

    _tprintf(_T("[SC] ChangeServiceConfig SUCCESS\n\n"));

done:
    if (bResult == FALSE)
        ReportLastError();

    if (hService)
        CloseServiceHandle(hService);

    if (hManager)
        CloseServiceHandle(hManager);

    return bResult;
}