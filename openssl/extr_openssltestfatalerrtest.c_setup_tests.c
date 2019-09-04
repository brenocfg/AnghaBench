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
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cert ; 
 int /*<<< orphan*/  privkey ; 
 int /*<<< orphan*/  test_fatalerr ; 
 int /*<<< orphan*/  test_get_argument (int) ; 

int setup_tests(void)
{
    if (!TEST_ptr(cert = test_get_argument(0))
            || !TEST_ptr(privkey = test_get_argument(1)))
        return 0;

    ADD_TEST(test_fatalerr);

    return 1;
}