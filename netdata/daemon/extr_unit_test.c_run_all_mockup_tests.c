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
 scalar_t__ check_number_printing () ; 
 scalar_t__ check_rrdcalc_comparisons () ; 
 scalar_t__ check_strdupz_path_subpath () ; 
 scalar_t__ run_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test1 ; 
 int /*<<< orphan*/  test10 ; 
 int /*<<< orphan*/  test11 ; 
 int /*<<< orphan*/  test12 ; 
 int /*<<< orphan*/  test13 ; 
 int /*<<< orphan*/  test14 ; 
 int /*<<< orphan*/  test14b ; 
 int /*<<< orphan*/  test14c ; 
 int /*<<< orphan*/  test15 ; 
 int /*<<< orphan*/  test2 ; 
 int /*<<< orphan*/  test3 ; 
 int /*<<< orphan*/  test4 ; 
 int /*<<< orphan*/  test5 ; 
 int /*<<< orphan*/  test5b ; 
 int /*<<< orphan*/  test6 ; 
 int /*<<< orphan*/  test7 ; 
 int /*<<< orphan*/  test8 ; 
 int /*<<< orphan*/  test9 ; 
 int /*<<< orphan*/  test_variable_renames () ; 

int run_all_mockup_tests(void)
{
    if(check_strdupz_path_subpath())
        return 1;

    if(check_number_printing())
        return 1;

    if(check_rrdcalc_comparisons())
        return 1;

    if(!test_variable_renames())
        return 1;

    if(run_test(&test1))
        return 1;

    if(run_test(&test2))
        return 1;

    if(run_test(&test3))
        return 1;

    if(run_test(&test4))
        return 1;

    if(run_test(&test5))
        return 1;

    if(run_test(&test5b))
        return 1;

    if(run_test(&test6))
        return 1;

    if(run_test(&test7))
        return 1;

    if(run_test(&test8))
        return 1;

    if(run_test(&test9))
        return 1;

    if(run_test(&test10))
        return 1;

    if(run_test(&test11))
        return 1;

    if(run_test(&test12))
        return 1;

    if(run_test(&test13))
        return 1;

    if(run_test(&test14))
        return 1;

    if(run_test(&test14b))
        return 1;

    if(run_test(&test14c))
        return 1;

    if(run_test(&test15))
        return 1;



    return 0;
}