#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mp_filter {TYPE_1__* in; } ;
struct filter_runner {int async_wakeup_sent; int /*<<< orphan*/  async_lock; int /*<<< orphan*/  wakeup_ctx; int /*<<< orphan*/  (* wakeup_cb ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  num_async_pending; int /*<<< orphan*/  async_pending; } ;
struct TYPE_2__ {int async_pending; struct filter_runner* runner; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mp_filter*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void filter_wakeup(struct mp_filter *f, bool mark_only)
{
    struct filter_runner *r = f->in->runner;
    pthread_mutex_lock(&r->async_lock);
    if (!f->in->async_pending) {
        f->in->async_pending = true;
        // (not using a talloc parent for thread safety reasons)
        MP_TARRAY_APPEND(NULL, r->async_pending, r->num_async_pending, f);
        if (!mark_only && !r->async_wakeup_sent) {
            if (r->wakeup_cb)
                r->wakeup_cb(r->wakeup_ctx);
            r->async_wakeup_sent = true;
        }
    }
    pthread_mutex_unlock(&r->async_lock);
}