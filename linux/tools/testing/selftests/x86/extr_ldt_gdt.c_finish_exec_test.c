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
 int /*<<< orphan*/  check_invalid_segment (int /*<<< orphan*/ ,int) ; 
 scalar_t__ nerrs ; 

__attribute__((used)) static int finish_exec_test(void)
{
	/*
	 * Older kernel versions did inherit the LDT on exec() which is
	 * wrong because exec() starts from a clean state.
	 */
	check_invalid_segment(0, 1);

	return nerrs ? 1 : 0;
}