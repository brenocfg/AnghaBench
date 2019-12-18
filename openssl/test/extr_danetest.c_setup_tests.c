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
 int /*<<< orphan*/  CAfile ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  basedomain ; 
 int /*<<< orphan*/  run_tlsatest ; 
 int /*<<< orphan*/  test_get_argument (int) ; 
 int /*<<< orphan*/  tlsafile ; 

int setup_tests(void)
{
    if (!TEST_ptr(basedomain = test_get_argument(0))
            || !TEST_ptr(CAfile = test_get_argument(1))
            || !TEST_ptr(tlsafile = test_get_argument(2)))
        return 0;

    ADD_TEST(run_tlsatest);
    return 1;
}