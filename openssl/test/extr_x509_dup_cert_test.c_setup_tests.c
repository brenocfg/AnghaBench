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
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  TEST_int_gt (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_509_dup_cert ; 
 size_t test_get_argument_count () ; 

int setup_tests(void)
{
    size_t n = test_get_argument_count();

    if (!TEST_int_gt(n, 0))
        return 0;

    ADD_ALL_TESTS(test_509_dup_cert, n);
    return 1;
}