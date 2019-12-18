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
struct timer_list {int /*<<< orphan*/  expires; } ;
struct timer_base {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 unsigned int calc_wheel_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enqueue_timer (struct timer_base*,struct timer_list*,unsigned int) ; 

__attribute__((used)) static void
__internal_add_timer(struct timer_base *base, struct timer_list *timer)
{
	unsigned int idx;

	idx = calc_wheel_index(timer->expires, base->clk);
	enqueue_timer(base, timer, idx);
}