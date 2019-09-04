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
typedef  int u64 ;
struct TYPE_2__ {scalar_t__ expires; } ;
struct alarm {TYPE_1__ node; } ;
typedef  int s64 ;
typedef  scalar_t__ ktime_t ;

/* Variables and functions */
 scalar_t__ ktime_add_ns (scalar_t__,int) ; 
 scalar_t__ ktime_add_safe (scalar_t__,scalar_t__) ; 
 int ktime_divns (scalar_t__,int) ; 
 scalar_t__ ktime_sub (scalar_t__,scalar_t__) ; 
 int ktime_to_ns (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

u64 alarm_forward(struct alarm *alarm, ktime_t now, ktime_t interval)
{
	u64 overrun = 1;
	ktime_t delta;

	delta = ktime_sub(now, alarm->node.expires);

	if (delta < 0)
		return 0;

	if (unlikely(delta >= interval)) {
		s64 incr = ktime_to_ns(interval);

		overrun = ktime_divns(delta, incr);

		alarm->node.expires = ktime_add_ns(alarm->node.expires,
							incr*overrun);

		if (alarm->node.expires > now)
			return overrun;
		/*
		 * This (and the ktime_add() below) is the
		 * correction for exact:
		 */
		overrun++;
	}

	alarm->node.expires = ktime_add_safe(alarm->node.expires, interval);
	return overrun;
}