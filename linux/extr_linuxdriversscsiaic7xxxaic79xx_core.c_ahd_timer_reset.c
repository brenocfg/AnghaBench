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
 int HZ ; 
 int /*<<< orphan*/  add_timer (struct timer_list*) ; 
 int /*<<< orphan*/  del_timer (struct timer_list*) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static void
ahd_timer_reset(struct timer_list *timer, int usec)
{
	del_timer(timer);
	timer->expires = jiffies + (usec * HZ)/1000000;
	add_timer(timer);
}