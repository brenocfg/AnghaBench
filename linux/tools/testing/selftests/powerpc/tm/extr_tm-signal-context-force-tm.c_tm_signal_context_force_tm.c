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
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  first_time ; 
 int /*<<< orphan*/  getcontext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  have_htm () ; 
 int /*<<< orphan*/  is_ppc64le () ; 
 int /*<<< orphan*/  main_context ; 
 int /*<<< orphan*/  tm_trap_test () ; 

int tm_signal_context_force_tm(void)
{
	SKIP_IF(!have_htm());
	/*
	 * Skipping if not running on 64 bits system, since I think it is
	 * not possible to set mcontext's [MSR] with TS, due to it being 32
	 * bits.
	 */
	SKIP_IF(!is_ppc64le());

	/* Will get back here after COUNT_MAX interactions */
	getcontext(&main_context);

	if (!first_time++)
		tm_trap_test();

	return EXIT_SUCCESS;
}