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
struct TYPE_2__ {scalar_t__ log_watcher_sent; scalar_t__ log_watcher_skipped; scalar_t__ log_worker_written; scalar_t__ log_worker_dropped; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATS_LOCK () ; 
 int /*<<< orphan*/  STATS_UNLOCK () ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  logger_key ; 
 scalar_t__ logger_stack_head ; 
 scalar_t__ logger_stack_tail ; 
 int /*<<< orphan*/  pthread_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ start_logger_thread () ; 
 TYPE_1__ stats ; 

void logger_init(void) {
    /* TODO: auto destructor when threads exit */
    /* TODO: error handling */

    /* init stack for iterating loggers */
    logger_stack_head = 0;
    logger_stack_tail = 0;
    pthread_key_create(&logger_key, NULL);

    if (start_logger_thread() != 0) {
        abort();
    }

    /* This can be removed once the global stats initializer is improved */
    STATS_LOCK();
    stats.log_worker_dropped = 0;
    stats.log_worker_written = 0;
    stats.log_watcher_skipped = 0;
    stats.log_watcher_sent = 0;
    STATS_UNLOCK();
    /* This is what adding a STDERR watcher looks like. should replace old
     * "verbose" settings. */
    //logger_add_watcher(NULL, 0);
    return;
}