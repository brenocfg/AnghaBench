#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int ngx_uint_t ;
typedef  size_t ngx_int_t ;
struct TYPE_5__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_cycle_t ;
struct TYPE_6__ {int /*<<< orphan*/ * handle; int /*<<< orphan*/  just_spawn; int /*<<< orphan*/  exiting; int /*<<< orphan*/ * pid; int /*<<< orphan*/ * name; int /*<<< orphan*/ * reopen; int /*<<< orphan*/ * quit; int /*<<< orphan*/ * term; } ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 scalar_t__ GetExitCodeProcess (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ NGX_INVALID_PID ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_CORE ; 
 int /*<<< orphan*/  NGX_LOG_NOTICE ; 
 int /*<<< orphan*/  ngx_close_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_errno ; 
 size_t ngx_last_process ; 
 int /*<<< orphan*/  ngx_log_debug5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,...) ; 
 TYPE_4__* ngx_processes ; 
 int /*<<< orphan*/  ngx_quit ; 
 scalar_t__ ngx_spawn_process (TYPE_1__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ngx_terminate ; 

__attribute__((used)) static ngx_uint_t
ngx_reap_worker(ngx_cycle_t *cycle, HANDLE h)
{
    u_long     code;
    ngx_int_t  n;

    for (n = 0; n < ngx_last_process; n++) {

        if (ngx_processes[n].handle != h) {
            continue;
        }

        if (GetExitCodeProcess(h, &code) == 0) {
            ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                          "GetExitCodeProcess(%P) failed",
                          ngx_processes[n].pid);
        }

        ngx_log_error(NGX_LOG_NOTICE, cycle->log, 0,
                      "%s process %P exited with code %Xl",
                      ngx_processes[n].name, ngx_processes[n].pid, code);

        ngx_close_handle(ngx_processes[n].reopen);
        ngx_close_handle(ngx_processes[n].quit);
        ngx_close_handle(ngx_processes[n].term);
        ngx_close_handle(h);

        ngx_processes[n].handle = NULL;
        ngx_processes[n].term = NULL;
        ngx_processes[n].quit = NULL;
        ngx_processes[n].reopen = NULL;

        if (!ngx_processes[n].exiting && !ngx_terminate && !ngx_quit) {

            if (ngx_spawn_process(cycle, ngx_processes[n].name, n)
                == NGX_INVALID_PID)
            {
                ngx_log_error(NGX_LOG_ALERT, cycle->log, 0,
                              "could not respawn %s", ngx_processes[n].name);

                if (n == ngx_last_process - 1) {
                    ngx_last_process--;
                }
            }
        }

        goto found;
    }

    ngx_log_error(NGX_LOG_ALERT, cycle->log, 0, "unknown process handle %p", h);

found:

    for (n = 0; n < ngx_last_process; n++) {

        ngx_log_debug5(NGX_LOG_DEBUG_CORE, cycle->log, 0,
                       "process: %d %P %p e:%d j:%d",
                       n,
                       ngx_processes[n].pid,
                       ngx_processes[n].handle,
                       ngx_processes[n].exiting,
                       ngx_processes[n].just_spawn);

        if (ngx_processes[n].handle) {
            return 1;
        }
    }

    return 0;
}