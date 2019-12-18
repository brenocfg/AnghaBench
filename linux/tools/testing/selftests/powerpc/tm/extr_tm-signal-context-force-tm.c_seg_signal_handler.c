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
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 scalar_t__ COUNT_MAX ; 
 scalar_t__ count ; 
 int /*<<< orphan*/  init_context ; 
 int /*<<< orphan*/  main_context ; 
 int /*<<< orphan*/  setcontext (int /*<<< orphan*/ *) ; 

void seg_signal_handler(int signo, siginfo_t *si, void *uc)
{
	if (count == COUNT_MAX) {
		/* Return to tm_signal_force_msr() and exit */
		setcontext(&main_context);
	}

	count++;

	/* Reexecute the test */
	setcontext(&init_context);
}