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
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_ALL_TESTS_NOSUBTEST (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_info (char*) ; 
 int /*<<< orphan*/  test_gmtime ; 

int setup_tests(void)
{
    if (sizeof(time_t) < 8)
        TEST_info("Skipping; time_t is less than 64-bits");
    else
        ADD_ALL_TESTS_NOSUBTEST(test_gmtime, 1000000);
    return 1;
}