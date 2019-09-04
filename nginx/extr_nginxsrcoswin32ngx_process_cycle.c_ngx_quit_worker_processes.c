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
typedef  scalar_t__ ngx_uint_t ;
typedef  size_t ngx_int_t ;
struct TYPE_4__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_cycle_t ;
struct TYPE_5__ {int exiting; int /*<<< orphan*/  quit_event; int /*<<< orphan*/  quit; int /*<<< orphan*/ * handle; scalar_t__ just_spawn; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_CORE ; 
 scalar_t__ SetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_errno ; 
 size_t ngx_last_process ; 
 int /*<<< orphan*/  ngx_log_debug5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_processes ; 

__attribute__((used)) static void
ngx_quit_worker_processes(ngx_cycle_t *cycle, ngx_uint_t old)
{
    ngx_int_t  n;

    for (n = 0; n < ngx_last_process; n++) {

        ngx_log_debug5(NGX_LOG_DEBUG_CORE, cycle->log, 0,
                       "process: %d %P %p e:%d j:%d",
                       n,
                       ngx_processes[n].pid,
                       ngx_processes[n].handle,
                       ngx_processes[n].exiting,
                       ngx_processes[n].just_spawn);

        if (old && ngx_processes[n].just_spawn) {
            ngx_processes[n].just_spawn = 0;
            continue;
        }

        if (ngx_processes[n].handle == NULL) {
            continue;
        }

        if (SetEvent(ngx_processes[n].quit) == 0) {
            ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                          "SetEvent(\"%s\") failed",
                          ngx_processes[n].quit_event);
        }

        ngx_processes[n].exiting = 1;
    }
}