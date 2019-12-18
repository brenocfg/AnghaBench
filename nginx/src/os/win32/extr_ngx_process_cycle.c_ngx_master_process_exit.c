#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_7__ {int /*<<< orphan*/  pool; TYPE_1__** modules; int /*<<< orphan*/  log; } ;
typedef  TYPE_2__ ngx_cycle_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* exit_master ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_NOTICE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_cache_manager_mutex ; 
 int /*<<< orphan*/  ngx_close_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_delete_pidfile (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_destroy_pool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_master_process_event ; 
 int /*<<< orphan*/  ngx_quit_event ; 
 int /*<<< orphan*/  ngx_reload_event ; 
 int /*<<< orphan*/  ngx_reopen_event ; 
 int /*<<< orphan*/  ngx_stop_event ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void
ngx_master_process_exit(ngx_cycle_t *cycle)
{
    ngx_uint_t  i;

    ngx_delete_pidfile(cycle);

    ngx_close_handle(ngx_cache_manager_mutex);
    ngx_close_handle(ngx_stop_event);
    ngx_close_handle(ngx_quit_event);
    ngx_close_handle(ngx_reopen_event);
    ngx_close_handle(ngx_reload_event);
    ngx_close_handle(ngx_master_process_event);

    ngx_log_error(NGX_LOG_NOTICE, cycle->log, 0, "exit");

    for (i = 0; cycle->modules[i]; i++) {
        if (cycle->modules[i]->exit_master) {
            cycle->modules[i]->exit_master(cycle);
        }
    }

    ngx_destroy_pool(cycle->pool);

    exit(0);
}