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
struct interval {scalar_t__ future_trigger; } ;
typedef  scalar_t__ interval_t ;

/* Variables and functions */
 int /*<<< orphan*/  D_INTERVAL ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ now ; 

__attribute__((used)) static inline void
interval_future_trigger(struct interval *top, interval_t wakeup)
{
    if (wakeup)
    {
#if INTERVAL_DEBUG
        dmsg(D_INTERVAL, "INTERVAL interval_future_trigger %d", (int)wakeup);
#endif
        top->future_trigger = now + wakeup;
    }
}