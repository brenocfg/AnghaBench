#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  dwContext; } ;
struct TYPE_10__ {TYPE_8__ hdr; TYPE_3__* netconn; } ;
typedef  TYPE_2__ http_request_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_11__ {scalar_t__ keep_until; int /*<<< orphan*/  pool_entry; TYPE_1__* server; scalar_t__ keep_alive; } ;
struct TYPE_9__ {int /*<<< orphan*/  conn_pool; } ;
typedef  scalar_t__ HMODULE ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ DWORD64 ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ COLLECT_TIME ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FreeLibrary (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS ; 
 int /*<<< orphan*/  GetModuleHandleExW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__*) ; 
 scalar_t__ GetTickCount () ; 
 int /*<<< orphan*/  INTERNET_STATUS_CLOSING_CONNECTION ; 
 int /*<<< orphan*/  INTERNET_STATUS_CONNECTION_CLOSED ; 
 int /*<<< orphan*/  INTERNET_SendCallback (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,TYPE_3__*,int) ; 
 scalar_t__ TRUE ; 
 scalar_t__ WININET_hModule ; 
 int /*<<< orphan*/  close_netconn (TYPE_3__*) ; 
 int /*<<< orphan*/  collect_connections_proc ; 
 scalar_t__ collector_running ; 
 int /*<<< orphan*/  connection_pool_cs ; 
 int /*<<< orphan*/  is_valid_netconn (TYPE_3__*) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void http_release_netconn(http_request_t *req, BOOL reuse)
{
    TRACE("%p %p %x\n",req, req->netconn, reuse);

    if(!is_valid_netconn(req->netconn))
        return;

#ifndef __REACTOS__
    if(reuse && req->netconn->keep_alive) {
        BOOL run_collector;

        EnterCriticalSection(&connection_pool_cs);

        list_add_head(&req->netconn->server->conn_pool, &req->netconn->pool_entry);
        req->netconn->keep_until = (DWORD64)GetTickCount() + COLLECT_TIME;
        req->netconn = NULL;

        run_collector = !collector_running;
        collector_running = TRUE;

        LeaveCriticalSection(&connection_pool_cs);

        if(run_collector) {
            HANDLE thread = NULL;
            HMODULE module;

            GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (const WCHAR*)WININET_hModule, &module);
            if(module)
                thread = CreateThread(NULL, 0, collect_connections_proc, NULL, 0, NULL);
            if(!thread) {
                EnterCriticalSection(&connection_pool_cs);
                collector_running = FALSE;
                LeaveCriticalSection(&connection_pool_cs);

                if(module)
                    FreeLibrary(module);
            }
            else
                CloseHandle(thread);
        }
        return;
    }
#else
    /* Silence unused function warning */
    (void)collect_connections_proc;
#endif

    INTERNET_SendCallback(&req->hdr, req->hdr.dwContext,
                          INTERNET_STATUS_CLOSING_CONNECTION, 0, 0);

    close_netconn(req->netconn);

    INTERNET_SendCallback(&req->hdr, req->hdr.dwContext,
                          INTERNET_STATUS_CONNECTION_CLOSED, 0, 0);
}