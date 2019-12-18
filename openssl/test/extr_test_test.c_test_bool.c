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
 int /*<<< orphan*/  TEST (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_false (int) ; 
 int /*<<< orphan*/  TEST_true (int) ; 

__attribute__((used)) static int test_bool(void)
{
    if (!TEST(0, TEST_true(0))
        | !TEST(1, TEST_true(1))
        | !TEST(1, TEST_false(0))
        | !TEST(0, TEST_false(1)))
        goto err;
    return 1;

err:
    return 0;
}