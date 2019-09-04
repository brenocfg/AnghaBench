#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_int_t ;
struct TYPE_4__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_cycle_t ;
struct TYPE_5__ {int /*<<< orphan*/  reopen_event; int /*<<< orphan*/  reopen; int /*<<< orphan*/ * handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 scalar_t__ SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_errno ; 
 size_t ngx_last_process ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_processes ; 

__attribute__((used)) static void
ngx_reopen_worker_processes(ngx_cycle_t *cycle)
{
    ngx_int_t  n;

    for (n = 0; n < ngx_last_process; n++) {

        if (ngx_processes[n].handle == NULL) {
            continue;
        }

        if (SetEvent(ngx_processes[n].reopen) == 0) {
            ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                          "SetEvent(\"%s\") failed",
                          ngx_processes[n].reopen_event);
        }
    }
}