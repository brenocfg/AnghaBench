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
struct TYPE_2__ {int lru_maintainer_thread; } ;

/* Variables and functions */
 scalar_t__ do_run_lru_maintainer_thread ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  lru_maintainer_lock ; 
 int /*<<< orphan*/  lru_maintainer_tid ; 
 int pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ settings ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 

int stop_lru_maintainer_thread(void) {
    int ret;
    pthread_mutex_lock(&lru_maintainer_lock);
    /* LRU thread is a sleep loop, will die on its own */
    do_run_lru_maintainer_thread = 0;
    pthread_mutex_unlock(&lru_maintainer_lock);
    if ((ret = pthread_join(lru_maintainer_tid, NULL)) != 0) {
        fprintf(stderr, "Failed to stop LRU maintainer thread: %s\n", strerror(ret));
        return -1;
    }
    settings.lru_maintainer_thread = false;
    return 0;
}