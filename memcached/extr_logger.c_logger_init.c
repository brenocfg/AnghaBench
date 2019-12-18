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
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  logger_key ; 
 scalar_t__ logger_stack_head ; 
 scalar_t__ logger_stack_tail ; 
 int /*<<< orphan*/  pthread_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ start_logger_thread () ; 

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

    /* This is what adding a STDERR watcher looks like. should replace old
     * "verbose" settings. */
    //logger_add_watcher(NULL, 0);
    return;
}