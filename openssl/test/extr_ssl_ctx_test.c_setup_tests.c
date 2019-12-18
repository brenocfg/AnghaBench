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
typedef  int /*<<< orphan*/  version_testdata ;
typedef  int /*<<< orphan*/  version_test ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_set_min_max_version ; 

int setup_tests(void)
{
    ADD_ALL_TESTS(test_set_min_max_version, sizeof(version_testdata) / sizeof(version_test));
    return 1;
}