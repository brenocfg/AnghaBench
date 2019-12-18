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
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  suspend_test_start_time ; 

void suspend_test_start(void)
{
	/* FIXME Use better timebase than "jiffies", ideally a clocksource.
	 * What we want is a hardware counter that will work correctly even
	 * during the irqs-are-off stages of the suspend/resume cycle...
	 */
	suspend_test_start_time = jiffies;
}