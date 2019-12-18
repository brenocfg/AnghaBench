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
 int /*<<< orphan*/  test_idea_cbc ; 
 int /*<<< orphan*/  test_idea_cfb64 ; 
 int /*<<< orphan*/  test_idea_ecb ; 

int setup_tests(void)
{
#ifndef OPENSSL_NO_IDEA
    ADD_TEST(test_idea_ecb);
    ADD_TEST(test_idea_cbc);
    ADD_TEST(test_idea_cfb64);
#endif
    return 1;
}