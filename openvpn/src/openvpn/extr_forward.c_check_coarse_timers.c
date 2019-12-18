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
typedef  scalar_t__ time_t ;
struct TYPE_2__ {scalar_t__ const coarse_timer_wakeup; } ;
struct context {TYPE_1__ c2; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_coarse_timers_dowork (struct context*) ; 
 int /*<<< orphan*/  context_reschedule_sec (struct context*,scalar_t__ const) ; 
 scalar_t__ now ; 

__attribute__((used)) static inline void
check_coarse_timers(struct context *c)
{
    const time_t local_now = now;
    if (local_now >= c->c2.coarse_timer_wakeup)
    {
        check_coarse_timers_dowork(c);
    }
    else
    {
        context_reschedule_sec(c, c->c2.coarse_timer_wakeup - local_now);
    }
}