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
 int /*<<< orphan*/  test_cipherbyname ; 
 int /*<<< orphan*/  test_digestbyname ; 
 int /*<<< orphan*/  test_namemap_independent ; 
 int /*<<< orphan*/  test_namemap_stored ; 

int setup_tests(void)
{
    ADD_TEST(test_namemap_independent);
    ADD_TEST(test_namemap_stored);
    ADD_TEST(test_digestbyname);
    ADD_TEST(test_cipherbyname);
    return 1;
}