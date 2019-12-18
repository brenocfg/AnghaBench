#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_tid_t ;
struct TYPE_5__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_cycle_t ;

/* Variables and functions */
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  ngx_console_init (TYPE_1__*) ; 
 scalar_t__ ngx_create_signal_events (TYPE_1__*) ; 
 scalar_t__ ngx_create_thread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stop_event ; 
 int /*<<< orphan*/  ngx_worker_thread ; 

void
ngx_single_process_cycle(ngx_cycle_t *cycle)
{
    ngx_tid_t  tid;

    ngx_console_init(cycle);

    if (ngx_create_signal_events(cycle) != NGX_OK) {
        exit(2);
    }

    if (ngx_create_thread(&tid, ngx_worker_thread, NULL, cycle->log) != 0) {
        /* fatal */
        exit(2);
    }

    /* STUB */
    WaitForSingleObject(ngx_stop_event, INFINITE);
}