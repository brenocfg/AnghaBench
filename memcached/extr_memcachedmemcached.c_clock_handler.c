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
struct timeval {int tv_sec; int /*<<< orphan*/  tv_usec; } ;
typedef  scalar_t__ rel_time_t ;
struct TYPE_2__ {int /*<<< orphan*/  curr_items; } ;

/* Variables and functions */
 int /*<<< orphan*/  assoc_start_expand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clockevent ; 
 scalar_t__ current_time ; 
 int /*<<< orphan*/  event_base_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_add (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  evtimer_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_set (int /*<<< orphan*/ *,void (*) (int const,short const,void*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  main_base ; 
 int process_started ; 
 TYPE_1__ stats_state ; 

__attribute__((used)) static void clock_handler(const int fd, const short which, void *arg) {
    struct timeval t = {.tv_sec = 1, .tv_usec = 0};
    static bool initialized = false;
#if defined(HAVE_CLOCK_GETTIME) && defined(CLOCK_MONOTONIC)
    static bool monotonic = false;
    static time_t monotonic_start;
#endif

    if (initialized) {
        /* only delete the event if it's actually there. */
        evtimer_del(&clockevent);
    } else {
        initialized = true;
        /* process_started is initialized to time() - 2. We initialize to 1 so
         * flush_all won't underflow during tests. */
#if defined(HAVE_CLOCK_GETTIME) && defined(CLOCK_MONOTONIC)
        struct timespec ts;
        if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0) {
            monotonic = true;
            monotonic_start = ts.tv_sec - ITEM_UPDATE_INTERVAL - 2;
        }
#endif
    }

    // While we're here, check for hash table expansion.
    // This function should be quick to avoid delaying the timer.
    assoc_start_expand(stats_state.curr_items);

    evtimer_set(&clockevent, clock_handler, 0);
    event_base_set(main_base, &clockevent);
    evtimer_add(&clockevent, &t);

#if defined(HAVE_CLOCK_GETTIME) && defined(CLOCK_MONOTONIC)
    if (monotonic) {
        struct timespec ts;
        if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1)
            return;
        current_time = (rel_time_t) (ts.tv_sec - monotonic_start);
        return;
    }
#endif
    {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        current_time = (rel_time_t) (tv.tv_sec - process_started);
    }
}