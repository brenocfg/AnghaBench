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
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOTAL_NUM_TESTS ; 
 int /*<<< orphan*/  sessionfile ; 
 int /*<<< orphan*/  test_client_hello ; 
 int /*<<< orphan*/  test_get_argument (int /*<<< orphan*/ ) ; 

int setup_tests(void)
{
    if (!TEST_ptr(sessionfile = test_get_argument(0)))
        return 0;

    ADD_ALL_TESTS(test_client_hello, TOTAL_NUM_TESTS);
    return 1;
}