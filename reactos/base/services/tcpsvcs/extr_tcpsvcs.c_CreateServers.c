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
typedef  int /*<<< orphan*/  WSADATA ;
typedef  char WCHAR ;
struct TYPE_3__ {char* lpName; } ;
typedef  int /*<<< orphan*/  PSERVICEINFO ;
typedef  int INT ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  char* DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  LOG_ALL ; 
 int /*<<< orphan*/  LOG_FILE ; 
 int /*<<< orphan*/  LogEvent (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int NUM_SERVICES ; 
 int /*<<< orphan*/  SERVICE_RUNNING ; 
 TYPE_1__* Services ; 
 int /*<<< orphan*/  StartServer ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UpdateStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WSACleanup () ; 
 char* WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WaitForMultipleObjects (int,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swprintf (char*,char*,char*) ; 

__attribute__((used)) static BOOL
CreateServers(PSERVICEINFO pServInfo)
{
    DWORD dwThreadId[NUM_SERVICES];
    HANDLE hThread[NUM_SERVICES];
    WSADATA wsaData;
    WCHAR buf[256];
    INT i;
    DWORD RetVal;

    if ((RetVal = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0)
    {
        swprintf(buf, L"WSAStartup() failed : %lu\n", RetVal);
        LogEvent(buf, 0, 100, LOG_ALL);
        return FALSE;
    }

    UpdateStatus(pServInfo, 0, 1);

    LogEvent(L"\nCreating server Threads", 0, 0, LOG_FILE);

    /* Create worker threads. */
    for (i = 0; i < NUM_SERVICES; i++)
    {
        swprintf(buf, L"Creating thread for %s server", Services[i].lpName);
        LogEvent(buf, 0, 0, LOG_FILE);

        hThread[i] = CreateThread(NULL,
                                  0,
                                  StartServer,
                                  &Services[i],
                                  0,
                                  &dwThreadId[i]);

        if (hThread[i] == NULL)
        {
            swprintf(buf, L"\nError creating %s server thread\n", Services[i].lpName);
            LogEvent(buf, GetLastError(), 0, LOG_ALL);
            return FALSE;
        }

        UpdateStatus(pServInfo, 0, 1);
    }

    LogEvent(L"Setting service status to running", 0, 0, LOG_FILE);
    UpdateStatus(pServInfo, SERVICE_RUNNING, 0);

    /* Wait until all threads have terminated. */
    WaitForMultipleObjects(NUM_SERVICES, hThread, TRUE, INFINITE);

    for (i = 0; i < NUM_SERVICES; i++)
    {
        if (hThread[i] != NULL)
            CloseHandle(hThread[i]);
    }

    LogEvent(L"Detaching Winsock2", 0, 0, LOG_FILE);
    WSACleanup();

    return TRUE;
}