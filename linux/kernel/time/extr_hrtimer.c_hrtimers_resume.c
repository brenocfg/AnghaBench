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
 int /*<<< orphan*/  clock_was_set_delayed () ; 
 int /*<<< orphan*/  lockdep_assert_irqs_disabled () ; 
 int /*<<< orphan*/  retrigger_next_event (int /*<<< orphan*/ *) ; 

void hrtimers_resume(void)
{
	lockdep_assert_irqs_disabled();
	/* Retrigger on the local CPU */
	retrigger_next_event(NULL);
	/* And schedule a retrigger for all others */
	clock_was_set_delayed();
}