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
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_info (char*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_srp (char*,char*,char*) ; 

__attribute__((used)) static int run_srp_tests(void)
{
    /* "Negative" test, expect a mismatch */
    TEST_info("run_srp: expecting a mismatch");
    if (!TEST_false(run_srp("alice", "password1", "password2")))
        return 0;

    /* "Positive" test, should pass */
    TEST_info("run_srp: expecting a match");
    if (!TEST_true(run_srp("alice", "password", "password")))
        return 0;

    return 1;
}