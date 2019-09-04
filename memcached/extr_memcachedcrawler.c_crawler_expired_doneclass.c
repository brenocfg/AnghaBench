#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct crawler_expired_data {int /*<<< orphan*/  lock; TYPE_1__* crawlerstats; } ;
struct TYPE_5__ {scalar_t__ data; } ;
typedef  TYPE_2__ crawler_module_t ;
struct TYPE_4__ {int run_complete; int /*<<< orphan*/  end_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_time ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void crawler_expired_doneclass(crawler_module_t *cm, int slab_cls) {
    struct crawler_expired_data *d = (struct crawler_expired_data *) cm->data;
    pthread_mutex_lock(&d->lock);
    d->crawlerstats[slab_cls].end_time = current_time;
    d->crawlerstats[slab_cls].run_complete = true;
    pthread_mutex_unlock(&d->lock);
}