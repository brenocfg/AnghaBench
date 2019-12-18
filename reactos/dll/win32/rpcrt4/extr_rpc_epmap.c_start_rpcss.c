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
typedef  int /*<<< orphan*/  status ;
typedef  char WCHAR ;
typedef  int ULONGLONG ;
struct TYPE_2__ {scalar_t__ dwCurrentState; } ;
typedef  TYPE_1__ SERVICE_STATUS_PROCESS ;
typedef  int /*<<< orphan*/  SC_HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ ERROR_SERVICE_ALREADY_RUNNING ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 int GetTickCount64 () ; 
 int /*<<< orphan*/  OpenSCManagerW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenServiceW (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  QueryServiceStatusEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SC_STATUS_PROCESS_INFO ; 
 int SERVICE_QUERY_STATUS ; 
 scalar_t__ SERVICE_RUNNING ; 
 int SERVICE_START ; 
 scalar_t__ SERVICE_START_PENDING ; 
 int /*<<< orphan*/  Sleep (int) ; 
 scalar_t__ StartServiceW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 

__attribute__((used)) static BOOL start_rpcss(void)
{
    static const WCHAR rpcssW[] = {'R','p','c','S','s',0};
    SC_HANDLE scm, service;
    SERVICE_STATUS_PROCESS status;
    BOOL ret = FALSE;

    TRACE("\n");

    if (!(scm = OpenSCManagerW( NULL, NULL, 0 )))
    {
        ERR( "failed to open service manager\n" );
        return FALSE;
    }
    if (!(service = OpenServiceW( scm, rpcssW, SERVICE_START | SERVICE_QUERY_STATUS )))
    {
        ERR( "failed to open RpcSs service\n" );
        CloseServiceHandle( scm );
        return FALSE;
    }
    if (StartServiceW( service, 0, NULL ) || GetLastError() == ERROR_SERVICE_ALREADY_RUNNING)
    {
        ULONGLONG start_time = GetTickCount64();
        do
        {
            DWORD dummy;

            if (!QueryServiceStatusEx( service, SC_STATUS_PROCESS_INFO,
                                       (BYTE *)&status, sizeof(status), &dummy ))
                break;
            if (status.dwCurrentState == SERVICE_RUNNING)
            {
                ret = TRUE;
                break;
            }
            if (GetTickCount64() - start_time > 30000) break;
            Sleep( 100 );

        } while (status.dwCurrentState == SERVICE_START_PENDING);

        if (status.dwCurrentState != SERVICE_RUNNING)
            WARN( "RpcSs failed to start %u\n", status.dwCurrentState );
    }
    else ERR( "failed to start RpcSs service\n" );

    CloseServiceHandle( service );
    CloseServiceHandle( scm );
    return ret;
}