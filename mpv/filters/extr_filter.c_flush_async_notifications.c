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
struct filter_runner {int num_async_pending; int async_wakeup_sent; int /*<<< orphan*/  async_lock; struct mp_filter** async_pending; } ;
struct TYPE_2__ {int async_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_pending (struct mp_filter*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void flush_async_notifications(struct filter_runner *r)
{
    pthread_mutex_lock(&r->async_lock);
    for (int n = 0; n < r->num_async_pending; n++) {
        struct mp_filter *f = r->async_pending[n];
        add_pending(f);
        f->in->async_pending = false;
    }
    r->num_async_pending = 0;
    r->async_wakeup_sent = false;
    pthread_mutex_unlock(&r->async_lock);
}