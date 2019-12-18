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
 int /*<<< orphan*/  EXECUTE_TEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXTURE ; 
 int /*<<< orphan*/  SETUP_TEST_FIXTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int result ; 
 int /*<<< orphan*/  set_up ; 
 int /*<<< orphan*/  tear_down ; 
 int /*<<< orphan*/ * tests ; 

__attribute__((used)) static int test_pass_key(int n)
{
    SETUP_TEST_FIXTURE(FIXTURE, set_up);
    EXECUTE_TEST(tests[n], tear_down);
    return result;
}