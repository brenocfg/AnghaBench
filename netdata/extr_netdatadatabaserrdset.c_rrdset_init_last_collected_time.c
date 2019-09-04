#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ usec_t ;
struct TYPE_6__ {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_5__ {TYPE_3__ last_collected_time; } ;
typedef  TYPE_1__ RRDSET ;

/* Variables and functions */
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  last_collected_time_align (TYPE_1__*) ; 
 int /*<<< orphan*/  now_realtime_timeval (TYPE_3__*) ; 

__attribute__((used)) static inline usec_t rrdset_init_last_collected_time(RRDSET *st) {
    now_realtime_timeval(&st->last_collected_time);
    last_collected_time_align(st);

    usec_t last_collect_ut = st->last_collected_time.tv_sec * USEC_PER_SEC + st->last_collected_time.tv_usec;

    #ifdef NETDATA_INTERNAL_CHECKS
    rrdset_debug(st, "initialized last collected time to %0.3" LONG_DOUBLE_MODIFIER, (LONG_DOUBLE)last_collect_ut / USEC_PER_SEC);
    #endif

    return last_collect_ut;
}