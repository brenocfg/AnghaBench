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
 int /*<<< orphan*/  infile ; 
 int /*<<< orphan*/  test_get_argument (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_pathlen ; 

int setup_tests(void)
{
    if (!TEST_ptr(infile = test_get_argument(0)))
        return 0;

    ADD_TEST(test_pathlen);
    return 1;
}