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
typedef  int /*<<< orphan*/  time_t ;
struct interval {scalar_t__ future_trigger; scalar_t__ refresh; scalar_t__ last_test_true; } ;
typedef  scalar_t__ interval_t ;

/* Variables and functions */
 int /*<<< orphan*/  D_INTERVAL ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  interval_earliest_wakeup (scalar_t__*,scalar_t__,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  now ; 

__attribute__((used)) static inline void
interval_schedule_wakeup(struct interval *top, interval_t *wakeup)
{
    const time_t local_now = now;
    interval_earliest_wakeup(wakeup, top->last_test_true + top->refresh, local_now);
    interval_earliest_wakeup(wakeup, top->future_trigger, local_now);
#if INTERVAL_DEBUG
    dmsg(D_INTERVAL, "INTERVAL interval_schedule wakeup=%d", (int)*wakeup);
#endif
}