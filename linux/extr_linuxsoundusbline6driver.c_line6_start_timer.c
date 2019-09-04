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
struct timer_list {void (* function ) (struct timer_list*) ;} ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (struct timer_list*,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (unsigned long) ; 

void line6_start_timer(struct timer_list *timer, unsigned long msecs,
		       void (*function)(struct timer_list *t))
{
	timer->function = function;
	mod_timer(timer, jiffies + msecs_to_jiffies(msecs));
}