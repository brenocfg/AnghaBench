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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  dwServiceFlags; int /*<<< orphan*/  dwProcessId; } ;
typedef  TYPE_1__* LPSERVICE_STATUS_PROCESS ;
typedef  int /*<<< orphan*/  LPSERVICE_STATUS ;
typedef  scalar_t__ LPCTSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  PrintServiceStatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,...) ; 

VOID
PrintService(LPCTSTR lpServiceName,
             LPCTSTR lpDisplayName,
             LPSERVICE_STATUS_PROCESS pStatus,
             BOOL bExtended)
{
    _tprintf(_T("SERVICE_NAME: %s\n"), lpServiceName);

    if (lpDisplayName)
        _tprintf(_T("DISPLAY_NAME: %s\n"), lpDisplayName);

    // Re-use PrintServiceStatus(), as SERVICE_STATUS_PROCESS is in fact an extension of SERVICE_STATUS.
    PrintServiceStatus((LPSERVICE_STATUS)pStatus);

    if (bExtended)
    {
        _tprintf(_T("\tPID                : %lu\n"),
            pStatus->dwProcessId);
        _tprintf(_T("\tFLAGS              : %lu\n"),
            pStatus->dwServiceFlags);
    }

    _tprintf(_T("\n"));
}