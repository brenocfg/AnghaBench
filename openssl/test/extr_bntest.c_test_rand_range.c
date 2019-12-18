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
 size_t OSSL_NELEM (int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_int_ge (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_note (char*) ; 
 int /*<<< orphan*/  binomial_critical ; 
 int /*<<< orphan*/  rand_range_cases ; 
 scalar_t__ test_rand_range_single (size_t) ; 

__attribute__((used)) static int test_rand_range(void)
{
    int n_success = 0;
    size_t i;

    for (i = 0; i < OSSL_NELEM(rand_range_cases); i++)
        n_success += test_rand_range_single(i);
    if (TEST_int_ge(n_success, binomial_critical))
        return 1;
    TEST_note("This test is expeced to fail by chance 0.01%% of the time.");
    return 0;
}