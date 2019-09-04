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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_pid_t ;
typedef  int ngx_int_t ;
struct TYPE_3__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_cycle_t ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_MODIFY_STATE ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int NGX_PROCESS_SYNC_NAME ; 
 int /*<<< orphan*/ * OpenEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SetEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_close_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ngx_sprintf (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_os_signal_process(ngx_cycle_t *cycle, char *sig, ngx_pid_t pid)
{
    HANDLE     ev;
    ngx_int_t  rc;
    char       evn[NGX_PROCESS_SYNC_NAME];

    ngx_sprintf((u_char *) evn, "Global\\ngx_%s_%P%Z", sig, pid);

    ev = OpenEvent(EVENT_MODIFY_STATE, 0, evn);
    if (ev == NULL) {
        ngx_log_error(NGX_LOG_ERR, cycle->log, ngx_errno,
                      "OpenEvent(\"%s\") failed", evn);
        return 1;
    }

    if (SetEvent(ev) == 0) {
        ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                      "SetEvent(\"%s\") failed", evn);
        rc = 1;

    } else {
        rc = 0;
    }

    ngx_close_handle(ev);

    return rc;
}