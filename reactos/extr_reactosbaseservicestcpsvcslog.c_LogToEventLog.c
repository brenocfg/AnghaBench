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
typedef  int /*<<< orphan*/  VOID ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseEventLog (scalar_t__) ; 
 int /*<<< orphan*/  EVENTLOG_ERROR_TYPE ; 
 int /*<<< orphan*/  EVENTLOG_SUCCESS ; 
 int LOG_ERROR ; 
 scalar_t__ RegisterEventSourceW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReportEventW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpEventSource ; 

__attribute__((used)) static VOID
LogToEventLog(LPCWSTR lpMsg,
              DWORD errNum,
              DWORD exitCode,
              UINT flags)
{
    HANDLE hEventLog;

    hEventLog = RegisterEventSourceW(NULL, lpEventSource);
    if (hEventLog)
    {
        ReportEventW(hEventLog,
                     (flags & LOG_ERROR) ? EVENTLOG_ERROR_TYPE : EVENTLOG_SUCCESS,
                     0,
                     0,
                     NULL,
                     1,
                     0,
                     &lpMsg,
                     NULL);

        CloseEventLog(hEventLog);
    }
}