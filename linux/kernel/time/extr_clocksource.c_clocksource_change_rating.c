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
struct clocksource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clocksource_change_rating (struct clocksource*,int) ; 
 int /*<<< orphan*/  clocksource_mutex ; 
 int /*<<< orphan*/  clocksource_select () ; 
 int /*<<< orphan*/  clocksource_select_watchdog (int) ; 
 int /*<<< orphan*/  clocksource_suspend_select (int) ; 
 int /*<<< orphan*/  clocksource_watchdog_lock (unsigned long*) ; 
 int /*<<< orphan*/  clocksource_watchdog_unlock (unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void clocksource_change_rating(struct clocksource *cs, int rating)
{
	unsigned long flags;

	mutex_lock(&clocksource_mutex);
	clocksource_watchdog_lock(&flags);
	__clocksource_change_rating(cs, rating);
	clocksource_watchdog_unlock(&flags);

	clocksource_select();
	clocksource_select_watchdog(false);
	clocksource_suspend_select(false);
	mutex_unlock(&clocksource_mutex);
}