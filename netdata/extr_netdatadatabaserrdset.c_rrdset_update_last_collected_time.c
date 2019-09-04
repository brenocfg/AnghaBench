#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int usec_t ;
typedef  int time_t ;
typedef  int suseconds_t ;
struct TYPE_4__ {int tv_sec; int tv_usec; } ;
struct TYPE_5__ {int usec_since_last_update; TYPE_1__ last_collected_time; } ;
typedef  TYPE_2__ RRDSET ;

/* Variables and functions */
 int USEC_PER_SEC ; 

__attribute__((used)) static inline usec_t rrdset_update_last_collected_time(RRDSET *st) {
    usec_t last_collect_ut = st->last_collected_time.tv_sec * USEC_PER_SEC + st->last_collected_time.tv_usec;
    usec_t ut = last_collect_ut + st->usec_since_last_update;
    st->last_collected_time.tv_sec = (time_t) (ut / USEC_PER_SEC);
    st->last_collected_time.tv_usec = (suseconds_t) (ut % USEC_PER_SEC);

    #ifdef NETDATA_INTERNAL_CHECKS
    rrdset_debug(st, "updated last collected time to %0.3" LONG_DOUBLE_MODIFIER, (LONG_DOUBLE)last_collect_ut / USEC_PER_SEC);
    #endif

    return last_collect_ut;
}