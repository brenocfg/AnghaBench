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
struct timer_list {scalar_t__ expires; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 unsigned long jiffies_delta_to_clock_t (scalar_t__) ; 
 scalar_t__ timer_pending (struct timer_list const*) ; 

unsigned long br_timer_value(const struct timer_list *timer)
{
	return timer_pending(timer)
		? jiffies_delta_to_clock_t(timer->expires - jiffies) : 0;
}