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
struct TYPE_2__ {int lru_crawler; } ;

/* Variables and functions */
 scalar_t__ do_run_lru_crawler_thread ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  item_crawler_tid ; 
 int /*<<< orphan*/  lru_crawler_cond ; 
 int /*<<< orphan*/  lru_crawler_lock ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ settings ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 

int stop_item_crawler_thread(void) {
    int ret;
    pthread_mutex_lock(&lru_crawler_lock);
    do_run_lru_crawler_thread = 0;
    pthread_cond_signal(&lru_crawler_cond);
    pthread_mutex_unlock(&lru_crawler_lock);
    if ((ret = pthread_join(item_crawler_tid, NULL)) != 0) {
        fprintf(stderr, "Failed to stop LRU crawler thread: %s\n", strerror(ret));
        return -1;
    }
    settings.lru_crawler = false;
    return 0;
}