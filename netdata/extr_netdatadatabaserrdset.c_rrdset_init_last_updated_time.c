#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ usec_t ;
struct TYPE_8__ {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_7__ {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_9__ {TYPE_2__ last_updated; scalar_t__ update_every; TYPE_1__ last_collected_time; } ;
typedef  TYPE_3__ RRDSET ;

/* Variables and functions */
 int /*<<< orphan*/  RRDSET_FLAG_STORE_FIRST ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  last_updated_time_align (TYPE_3__*) ; 
 scalar_t__ rrdset_flag_check (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline usec_t rrdset_init_last_updated_time(RRDSET *st) {
    // copy the last collected time to last updated time
    st->last_updated.tv_sec  = st->last_collected_time.tv_sec;
    st->last_updated.tv_usec = st->last_collected_time.tv_usec;

    if(rrdset_flag_check(st, RRDSET_FLAG_STORE_FIRST))
        st->last_updated.tv_sec -= st->update_every;

    last_updated_time_align(st);

    usec_t last_updated_ut = st->last_updated.tv_sec * USEC_PER_SEC + st->last_updated.tv_usec;

    #ifdef NETDATA_INTERNAL_CHECKS
    rrdset_debug(st, "initialized last updated time to %0.3" LONG_DOUBLE_MODIFIER, (LONG_DOUBLE)last_updated_ut / USEC_PER_SEC);
    #endif

    return last_updated_ut;
}