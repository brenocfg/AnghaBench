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
 int /*<<< orphan*/  fill_function_pointers () ; 
 scalar_t__ nerrs ; 
 int /*<<< orphan*/  test_clock_gettime () ; 
 int /*<<< orphan*/  test_getcpu () ; 
 int /*<<< orphan*/  test_gettimeofday () ; 

int main(int argc, char **argv)
{
	fill_function_pointers();

	test_clock_gettime();
	test_gettimeofday();

	/*
	 * Test getcpu() last so that, if something goes wrong setting affinity,
	 * we still run the other tests.
	 */
	test_getcpu();

	return nerrs ? 1 : 0;
}