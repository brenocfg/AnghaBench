#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {int /*<<< orphan*/  ServiceStatusProcess; void* lpDisplayName; void* lpServiceName; } ;
struct TYPE_6__ {int NumServices; TYPE_2__* pAllServices; } ;
typedef  int /*<<< orphan*/  SERVICE_STATUS_PROCESS ;
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  TYPE_1__* PMAIN_WND_INFO ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  TYPE_2__ ENUM_SERVICE_STATUS_PROCESS ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ EnumServicesStatusEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeServiceList (TYPE_1__*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * OpenSCManagerW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcessHeap ; 
 int /*<<< orphan*/  SC_ENUM_PROCESS_INFO ; 
 int /*<<< orphan*/  SC_MANAGER_ENUMERATE_SERVICE ; 
 int /*<<< orphan*/  SERVICE_STATE_ALL ; 
 int /*<<< orphan*/  SERVICE_WIN32 ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wcscpy (void*,void*) ; 
 int wcslen (void*) ; 

BOOL
GetServiceList(PMAIN_WND_INFO Info)
{
    ENUM_SERVICE_STATUS_PROCESS *pServices = NULL;
    SC_HANDLE ScHandle;
    BOOL bRet = FALSE;

    DWORD BytesNeeded = 0;
    DWORD ResumeHandle = 0;
    DWORD NumServices = 0;
    DWORD i;

    FreeServiceList(Info);

    ScHandle = OpenSCManagerW(NULL,
                              NULL,
                              SC_MANAGER_ENUMERATE_SERVICE);
    if (ScHandle != NULL)
    {
        if (!EnumServicesStatusEx(ScHandle,
                                  SC_ENUM_PROCESS_INFO,
                                  SERVICE_WIN32,
                                  SERVICE_STATE_ALL,
                                  NULL,
                                  0,
                                  &BytesNeeded,
                                  &NumServices,
                                  &ResumeHandle,
                                  0))
        {
            /* Call function again if required size was returned */
            if (GetLastError() == ERROR_MORE_DATA)
            {
                /* reserve memory for service info array */
                pServices = (ENUM_SERVICE_STATUS_PROCESS *)HeapAlloc(ProcessHeap,
                                                                     0,
                                                                     BytesNeeded);
                if (pServices)
                {
                    /* fill array with service info */
                    if (EnumServicesStatusEx(ScHandle,
                                             SC_ENUM_PROCESS_INFO,
                                             SERVICE_WIN32,
                                             SERVICE_STATE_ALL,
                                             (LPBYTE)pServices,
                                             BytesNeeded,
                                             &BytesNeeded,
                                             &NumServices,
                                             &ResumeHandle,
                                             0))
                    {
                        bRet = TRUE;
                    }
                }
            }
        }
    }

    if (ScHandle)
        CloseServiceHandle(ScHandle);

    Info->pAllServices = (ENUM_SERVICE_STATUS_PROCESS *)HeapAlloc(ProcessHeap,
                                                                  HEAP_ZERO_MEMORY,
                                                                  NumServices * sizeof(ENUM_SERVICE_STATUS_PROCESS));
    if (Info->pAllServices != NULL)
    {
        Info->NumServices = NumServices;

        for (i = 0; i < NumServices; i++)
        {
            Info->pAllServices[i].lpServiceName = HeapAlloc(ProcessHeap,
                                                            HEAP_ZERO_MEMORY,
                                                            (wcslen(pServices[i].lpServiceName) + 1) * sizeof(WCHAR));
            if (Info->pAllServices[i].lpServiceName)
                wcscpy(Info->pAllServices[i].lpServiceName, pServices[i].lpServiceName);

            Info->pAllServices[i].lpDisplayName = HeapAlloc(ProcessHeap,
                                                            HEAP_ZERO_MEMORY,
                                                            (wcslen(pServices[i].lpDisplayName) + 1) * sizeof(WCHAR));
            if (Info->pAllServices[i].lpDisplayName)
                wcscpy(Info->pAllServices[i].lpDisplayName, pServices[i].lpDisplayName);

            CopyMemory(&Info->pAllServices[i].ServiceStatusProcess,
                       &pServices[i].ServiceStatusProcess,
                       sizeof(SERVICE_STATUS_PROCESS));
        }
    }

    if (pServices)
        HeapFree(ProcessHeap, 0, pServices);

    return bRet;
}