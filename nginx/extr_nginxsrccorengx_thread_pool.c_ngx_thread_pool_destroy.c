#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_8__ {scalar_t__ active; } ;
struct TYPE_9__ {TYPE_1__ event; void* ctx; int /*<<< orphan*/  handler; } ;
typedef  TYPE_2__ ngx_thread_task_t ;
struct TYPE_10__ {scalar_t__ threads; int /*<<< orphan*/  log; int /*<<< orphan*/  mtx; int /*<<< orphan*/  cond; } ;
typedef  TYPE_3__ ngx_thread_pool_t ;

/* Variables and functions */
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ngx_sched_yield () ; 
 int /*<<< orphan*/  ngx_thread_cond_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_thread_mutex_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_thread_pool_exit_handler ; 
 scalar_t__ ngx_thread_task_post (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static void
ngx_thread_pool_destroy(ngx_thread_pool_t *tp)
{
    ngx_uint_t           n;
    ngx_thread_task_t    task;
    volatile ngx_uint_t  lock;

    ngx_memzero(&task, sizeof(ngx_thread_task_t));

    task.handler = ngx_thread_pool_exit_handler;
    task.ctx = (void *) &lock;

    for (n = 0; n < tp->threads; n++) {
        lock = 1;

        if (ngx_thread_task_post(tp, &task) != NGX_OK) {
            return;
        }

        while (lock) {
            ngx_sched_yield();
        }

        task.event.active = 0;
    }

    (void) ngx_thread_cond_destroy(&tp->cond, tp->log);

    (void) ngx_thread_mutex_destroy(&tp->mtx, tp->log);
}