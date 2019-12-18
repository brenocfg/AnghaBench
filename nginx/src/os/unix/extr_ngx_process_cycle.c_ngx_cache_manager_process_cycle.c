#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {void** data; int /*<<< orphan*/  log; int /*<<< orphan*/  handler; } ;
typedef  TYPE_1__ ngx_event_t ;
struct TYPE_12__ {int connection_n; int /*<<< orphan*/  log; } ;
typedef  TYPE_2__ ngx_cycle_t ;
struct TYPE_13__ {int /*<<< orphan*/  delay; int /*<<< orphan*/  name; int /*<<< orphan*/  handler; } ;
typedef  TYPE_3__ ngx_cache_manager_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_NOTICE ; 
 int /*<<< orphan*/  NGX_PROCESS_HELPER ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_close_listening_sockets (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ngx_process ; 
 int /*<<< orphan*/  ngx_process_events_and_timers (TYPE_2__*) ; 
 scalar_t__ ngx_quit ; 
 scalar_t__ ngx_reopen ; 
 int /*<<< orphan*/  ngx_reopen_files (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ngx_setproctitle (int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_terminate ; 
 scalar_t__ ngx_use_accept_mutex ; 
 int /*<<< orphan*/  ngx_worker_process_init (TYPE_2__*,int) ; 

__attribute__((used)) static void
ngx_cache_manager_process_cycle(ngx_cycle_t *cycle, void *data)
{
    ngx_cache_manager_ctx_t *ctx = data;

    void         *ident[4];
    ngx_event_t   ev;

    /*
     * Set correct process type since closing listening Unix domain socket
     * in a master process also removes the Unix domain socket file.
     */
    ngx_process = NGX_PROCESS_HELPER;

    ngx_close_listening_sockets(cycle);

    /* Set a moderate number of connections for a helper process. */
    cycle->connection_n = 512;

    ngx_worker_process_init(cycle, -1);

    ngx_memzero(&ev, sizeof(ngx_event_t));
    ev.handler = ctx->handler;
    ev.data = ident;
    ev.log = cycle->log;
    ident[3] = (void *) -1;

    ngx_use_accept_mutex = 0;

    ngx_setproctitle(ctx->name);

    ngx_add_timer(&ev, ctx->delay);

    for ( ;; ) {

        if (ngx_terminate || ngx_quit) {
            ngx_log_error(NGX_LOG_NOTICE, cycle->log, 0, "exiting");
            exit(0);
        }

        if (ngx_reopen) {
            ngx_reopen = 0;
            ngx_log_error(NGX_LOG_NOTICE, cycle->log, 0, "reopening logs");
            ngx_reopen_files(cycle, -1);
        }

        ngx_process_events_and_timers(cycle);
    }
}