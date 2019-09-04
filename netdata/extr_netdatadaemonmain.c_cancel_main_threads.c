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
typedef  scalar_t__ usec_t ;
struct TYPE_2__ {scalar_t__ enabled; int /*<<< orphan*/ * name; int /*<<< orphan*/ * thread; } ;

/* Variables and functions */
 scalar_t__ NETDATA_MAIN_THREAD_EXITED ; 
 scalar_t__ NETDATA_MAIN_THREAD_RUNNING ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error_log_limit_unlimited () ; 
 int /*<<< orphan*/  info (char*,...) ; 
 int netdata_exit ; 
 int /*<<< orphan*/  netdata_thread_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep_usec (scalar_t__) ; 
 TYPE_1__* static_threads ; 

void cancel_main_threads() {
    error_log_limit_unlimited();

    int i, found = 0;
    usec_t max = 5 * USEC_PER_SEC, step = 100000;
    for (i = 0; static_threads[i].name != NULL ; i++) {
        if(static_threads[i].enabled == NETDATA_MAIN_THREAD_RUNNING) {
            info("EXIT: Stopping master thread: %s", static_threads[i].name);
            netdata_thread_cancel(*static_threads[i].thread);
            found++;
        }
    }

    netdata_exit = 1;

    while(found && max > 0) {
        max -= step;
        info("Waiting %d threads to finish...", found);
        sleep_usec(step);
        found = 0;
        for (i = 0; static_threads[i].name != NULL ; i++) {
            if (static_threads[i].enabled != NETDATA_MAIN_THREAD_EXITED)
                found++;
        }
    }

    if(found) {
        for (i = 0; static_threads[i].name != NULL ; i++) {
            if (static_threads[i].enabled != NETDATA_MAIN_THREAD_EXITED)
                error("Master thread %s takes too long to exit. Giving up...", static_threads[i].name);
        }
    }
    else
        info("All threads finished.");
}