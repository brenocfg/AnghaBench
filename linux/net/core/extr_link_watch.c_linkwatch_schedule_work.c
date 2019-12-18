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

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  LW_URGENT ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  linkwatch_flags ; 
 unsigned long linkwatch_nextevent ; 
 int /*<<< orphan*/  linkwatch_work ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  system_wq ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void linkwatch_schedule_work(int urgent)
{
	unsigned long delay = linkwatch_nextevent - jiffies;

	if (test_bit(LW_URGENT, &linkwatch_flags))
		return;

	/* Minimise down-time: drop delay for up event. */
	if (urgent) {
		if (test_and_set_bit(LW_URGENT, &linkwatch_flags))
			return;
		delay = 0;
	}

	/* If we wrap around we'll delay it by at most HZ. */
	if (delay > HZ)
		delay = 0;

	/*
	 * If urgent, schedule immediate execution; otherwise, don't
	 * override the existing timer.
	 */
	if (test_bit(LW_URGENT, &linkwatch_flags))
		mod_delayed_work(system_wq, &linkwatch_work, 0);
	else
		schedule_delayed_work(&linkwatch_work, delay);
}