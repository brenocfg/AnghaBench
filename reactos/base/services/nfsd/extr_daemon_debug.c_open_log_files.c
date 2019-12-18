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

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  ReportStatusToSCMgr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERVICE_STOPPED ; 
 int /*<<< orphan*/ * dlog_file ; 
 int /*<<< orphan*/ * elog_file ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 void* fopen (char const*,char const*) ; 
 scalar_t__ g_debug_level ; 

void open_log_files()
{
    const char dfile[] = "nfsddbg.log";
    const char efile[] = "nfsderr.log";
    const char mode[] = "w";
    if (g_debug_level > 0) {
        dlog_file = fopen(dfile, mode);
        if (dlog_file == NULL) {
            ReportStatusToSCMgr(SERVICE_STOPPED, GetLastError(), 0);
            exit (GetLastError());
        }
    }
    elog_file = fopen(efile, mode);
    if (elog_file == NULL) {
        ReportStatusToSCMgr(SERVICE_STOPPED, GetLastError(), 0);
        exit (GetLastError());
    }
}