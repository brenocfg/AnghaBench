#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int useconds_t ;
struct logger_stats {int dummy; } ;
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ logger ;

/* Variables and functions */
 int /*<<< orphan*/  L_DEBUG (char*) ; 
 int MAX_LOGGER_SLEEP ; 
 int MIN_LOGGER_SLEEP ; 
 int /*<<< orphan*/  WATCHER_ALL ; 
 scalar_t__ do_run_logger_thread ; 
 TYPE_1__* logger_stack_head ; 
 int /*<<< orphan*/  logger_stack_lock ; 
 int /*<<< orphan*/  logger_thread_poll_watchers (int,int /*<<< orphan*/ ) ; 
 scalar_t__ logger_thread_read (TYPE_1__*,struct logger_stats*) ; 
 int /*<<< orphan*/  logger_thread_sum_stats (struct logger_stats*) ; 
 int /*<<< orphan*/  memset (struct logger_stats*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void *logger_thread(void *arg) {
    useconds_t to_sleep = MIN_LOGGER_SLEEP;
    L_DEBUG("LOGGER: Starting logger thread\n");
    // TODO: If we ever have item references in the logger code, will need to
    // ensure everything is dequeued before stopping the thread.
    while (do_run_logger_thread) {
        int found_logs = 0;
        logger *l;
        struct logger_stats ls;
        memset(&ls, 0, sizeof(struct logger_stats));

        /* only sleep if we're *above* the minimum */
        if (to_sleep > MIN_LOGGER_SLEEP)
            usleep(to_sleep);

        /* Call function to iterate each logger. */
        pthread_mutex_lock(&logger_stack_lock);
        for (l = logger_stack_head; l != NULL; l=l->next) {
            /* lock logger, call function to manipulate it */
            found_logs += logger_thread_read(l, &ls);
        }

        logger_thread_poll_watchers(1, WATCHER_ALL);
        pthread_mutex_unlock(&logger_stack_lock);

        /* TODO: abstract into a function and share with lru_crawler */
        if (!found_logs) {
            if (to_sleep < MAX_LOGGER_SLEEP)
                to_sleep += to_sleep / 8;
            if (to_sleep > MAX_LOGGER_SLEEP)
                to_sleep = MAX_LOGGER_SLEEP;
        } else {
            to_sleep /= 2;
            if (to_sleep < MIN_LOGGER_SLEEP)
                to_sleep = MIN_LOGGER_SLEEP;
        }
        logger_thread_sum_stats(&ls);
    }

    return NULL;
}