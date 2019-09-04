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
 int /*<<< orphan*/  check_mpx_insns_and_tables ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  run_timed_test (int /*<<< orphan*/ ) ; 

void mpx_table_test(void)
{
	printf("starting mpx bounds table test\n");
	run_timed_test(check_mpx_insns_and_tables);
	printf("done with mpx bounds table test\n");
}