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
struct hrtimer_sleeper {int /*<<< orphan*/  timer; } ;
typedef  enum hrtimer_mode { ____Placeholder_hrtimer_mode } hrtimer_mode ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int /*<<< orphan*/  __hrtimer_init_sleeper (struct hrtimer_sleeper*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debug_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void hrtimer_init_sleeper(struct hrtimer_sleeper *sl, clockid_t clock_id,
			  enum hrtimer_mode mode)
{
	debug_init(&sl->timer, clock_id, mode);
	__hrtimer_init_sleeper(sl, clock_id, mode);

}