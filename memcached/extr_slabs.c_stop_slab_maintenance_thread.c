#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ do_run_slab_rebalance_thread ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rebalance_tid ; 
 int /*<<< orphan*/  slab_rebalance_cond ; 
 int /*<<< orphan*/  slabs_rebalance_lock ; 

void stop_slab_maintenance_thread(void) {
    mutex_lock(&slabs_rebalance_lock);
    do_run_slab_rebalance_thread = 0;
    pthread_cond_signal(&slab_rebalance_cond);
    pthread_mutex_unlock(&slabs_rebalance_lock);

    /* Wait for the maintenance thread to stop */
    pthread_join(rebalance_tid, NULL);
}