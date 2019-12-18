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
struct TYPE_2__ {scalar_t__ done; int /*<<< orphan*/ * slab_start; } ;

/* Variables and functions */
 scalar_t__ do_run_slab_rebalance_thread ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ slab_rebal ; 
 int /*<<< orphan*/  slab_rebalance_cond ; 
 int /*<<< orphan*/  slab_rebalance_finish () ; 
 int slab_rebalance_move () ; 
 int slab_rebalance_signal ; 
 scalar_t__ slab_rebalance_start () ; 
 int /*<<< orphan*/  slabs_rebalance_lock ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void *slab_rebalance_thread(void *arg) {
    int was_busy = 0;
    int backoff_timer = 1;
    int backoff_max = 1000;
    /* So we first pass into cond_wait with the mutex held */
    mutex_lock(&slabs_rebalance_lock);

    /* Must finish moving page before stopping */
    while (slab_rebalance_signal || do_run_slab_rebalance_thread) {
        if (slab_rebalance_signal == 1) {
            if (slab_rebalance_start() < 0) {
                /* Handle errors with more specificity as required. */
                slab_rebalance_signal = 0;
            }

            was_busy = 0;
        } else if (slab_rebalance_signal && slab_rebal.slab_start != NULL) {
            was_busy = slab_rebalance_move();
        }

        if (slab_rebal.done) {
            slab_rebalance_finish();
        } else if (was_busy) {
            /* Stuck waiting for some items to unlock, so slow down a bit
             * to give them a chance to free up */
            usleep(backoff_timer);
            backoff_timer = backoff_timer * 2;
            if (backoff_timer > backoff_max)
                backoff_timer = backoff_max;
        }

        if (slab_rebalance_signal == 0) {
            /* always hold this lock while we're running */
            pthread_cond_wait(&slab_rebalance_cond, &slabs_rebalance_lock);
        }
    }

    // TODO: cancel in-flight slab page move
    mutex_unlock(&slabs_rebalance_lock);
    return NULL;
}