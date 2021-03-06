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
 int /*<<< orphan*/  test_default_cipherlist_clear ; 
 int /*<<< orphan*/  test_default_cipherlist_explicit ; 
 int /*<<< orphan*/  test_default_cipherlist_implicit ; 

int setup_tests(void)
{
    ADD_TEST(test_default_cipherlist_implicit);
    ADD_TEST(test_default_cipherlist_explicit);
    ADD_TEST(test_default_cipherlist_clear);
    return 1;
}