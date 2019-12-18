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
struct clocksource {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  clocksource_dequeue_watchdog (struct clocksource*) ; 
 scalar_t__ clocksource_is_suspend (struct clocksource*) ; 
 scalar_t__ clocksource_is_watchdog (struct clocksource*) ; 
 int /*<<< orphan*/  clocksource_select_fallback () ; 
 int /*<<< orphan*/  clocksource_select_watchdog (int) ; 
 int /*<<< orphan*/  clocksource_suspend_select (int) ; 
 int /*<<< orphan*/  clocksource_watchdog_lock (unsigned long*) ; 
 int /*<<< orphan*/  clocksource_watchdog_unlock (unsigned long*) ; 
 struct clocksource* curr_clocksource ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int clocksource_unbind(struct clocksource *cs)
{
	unsigned long flags;

	if (clocksource_is_watchdog(cs)) {
		/* Select and try to install a replacement watchdog. */
		clocksource_select_watchdog(true);
		if (clocksource_is_watchdog(cs))
			return -EBUSY;
	}

	if (cs == curr_clocksource) {
		/* Select and try to install a replacement clock source */
		clocksource_select_fallback();
		if (curr_clocksource == cs)
			return -EBUSY;
	}

	if (clocksource_is_suspend(cs)) {
		/*
		 * Select and try to install a replacement suspend clocksource.
		 * If no replacement suspend clocksource, we will just let the
		 * clocksource go and have no suspend clocksource.
		 */
		clocksource_suspend_select(true);
	}

	clocksource_watchdog_lock(&flags);
	clocksource_dequeue_watchdog(cs);
	list_del_init(&cs->list);
	clocksource_watchdog_unlock(&flags);

	return 0;
}