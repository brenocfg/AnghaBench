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
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  template_private_test ; 
 int /*<<< orphan*/  template_public_test ; 
 int /*<<< orphan*/  template_static_fail_test ; 
 int /*<<< orphan*/  template_static_params_test ; 

int setup_tests(void)
{
    ADD_TEST(template_public_test);
    ADD_TEST(template_private_test);
    ADD_ALL_TESTS(template_static_params_test, 2);
    ADD_ALL_TESTS(template_static_fail_test, 2);
    return 1;
}