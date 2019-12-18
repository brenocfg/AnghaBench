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
typedef  int /*<<< orphan*/  u32 ;
struct clocksource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clocksource_suspend_select (struct clocksource*) ; 
 int /*<<< orphan*/  __clocksource_update_freq_scale (struct clocksource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clocksource_arch_init (struct clocksource*) ; 
 int /*<<< orphan*/  clocksource_enqueue (struct clocksource*) ; 
 int /*<<< orphan*/  clocksource_enqueue_watchdog (struct clocksource*) ; 
 int /*<<< orphan*/  clocksource_mutex ; 
 int /*<<< orphan*/  clocksource_select () ; 
 int /*<<< orphan*/  clocksource_select_watchdog (int) ; 
 int /*<<< orphan*/  clocksource_watchdog_lock (unsigned long*) ; 
 int /*<<< orphan*/  clocksource_watchdog_unlock (unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int __clocksource_register_scale(struct clocksource *cs, u32 scale, u32 freq)
{
	unsigned long flags;

	clocksource_arch_init(cs);

	/* Initialize mult/shift and max_idle_ns */
	__clocksource_update_freq_scale(cs, scale, freq);

	/* Add clocksource to the clocksource list */
	mutex_lock(&clocksource_mutex);

	clocksource_watchdog_lock(&flags);
	clocksource_enqueue(cs);
	clocksource_enqueue_watchdog(cs);
	clocksource_watchdog_unlock(&flags);

	clocksource_select();
	clocksource_select_watchdog(false);
	__clocksource_suspend_select(cs);
	mutex_unlock(&clocksource_mutex);
	return 0;
}