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
 int ksft_exit_pass () ; 
 int /*<<< orphan*/  ksft_print_header () ; 
 int /*<<< orphan*/  test_membarrier () ; 
 int /*<<< orphan*/  test_membarrier_query () ; 

int main(int argc, char **argv)
{
	ksft_print_header();

	test_membarrier_query();
	test_membarrier();

	return ksft_exit_pass();
}