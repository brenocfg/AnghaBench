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
struct TYPE_2__ {int /*<<< orphan*/ * slab_start; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_SLAB_BULK_CHECK ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* getenv (char*) ; 
 scalar_t__ pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rebalance_tid ; 
 scalar_t__ slab_bulk_check ; 
 TYPE_1__ slab_rebal ; 
 int /*<<< orphan*/  slab_rebalance_cond ; 
 scalar_t__ slab_rebalance_signal ; 
 int /*<<< orphan*/  slab_rebalance_thread ; 
 int /*<<< orphan*/  slabs_rebalance_lock ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 

int start_slab_maintenance_thread(void) {
    int ret;
    slab_rebalance_signal = 0;
    slab_rebal.slab_start = NULL;
    char *env = getenv("MEMCACHED_SLAB_BULK_CHECK");
    if (env != NULL) {
        slab_bulk_check = atoi(env);
        if (slab_bulk_check == 0) {
            slab_bulk_check = DEFAULT_SLAB_BULK_CHECK;
        }
    }

    if (pthread_cond_init(&slab_rebalance_cond, NULL) != 0) {
        fprintf(stderr, "Can't initialize rebalance condition\n");
        return -1;
    }
    pthread_mutex_init(&slabs_rebalance_lock, NULL);

    if ((ret = pthread_create(&rebalance_tid, NULL,
                              slab_rebalance_thread, NULL)) != 0) {
        fprintf(stderr, "Can't create rebal thread: %s\n", strerror(ret));
        return -1;
    }
    return 0;
}