#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int num; int /*<<< orphan*/  test_case_name; } ;

/* Variables and functions */
 TYPE_1__* all_tests ; 
 int atoi (char*) ; 
 int num_tests ; 
 int single_iter ; 
 int single_test ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_printf_stderr (char*,char*,int,int,...) ; 

__attribute__((used)) static int check_single_test_params(char *name, char *testname, char *itname)
{
    if (name != NULL) {
        int i;
        for (i = 0; i < num_tests; ++i) {
            if (strcmp(name, all_tests[i].test_case_name) == 0) {
                single_test = 1 + i;
                break;
            }
        }
        if (i >= num_tests)
            single_test = atoi(name);
    }


    /* if only iteration is specified, assume we want the first test */
    if (single_test == -1 && single_iter != -1)
        single_test = 1;

    if (single_test != -1) {
        if (single_test < 1 || single_test > num_tests) {
            test_printf_stderr("Invalid -%s value "
                               "(Value must be a valid test name OR a value between %d..%d)\n",
                               testname, 1, num_tests);
            return 0;
        }
    }
    if (single_iter != -1) {
        if (all_tests[single_test - 1].num == -1) {
            test_printf_stderr("-%s option is not valid for test %d:%s\n",
                               itname,
                               single_test,
                               all_tests[single_test - 1].test_case_name);
            return 0;
        } else if (single_iter < 1
                   || single_iter > all_tests[single_test - 1].num) {
            test_printf_stderr("Invalid -%s value for test %d:%s\t"
                               "(Value must be in the range %d..%d)\n",
                               itname, single_test,
                               all_tests[single_test - 1].test_case_name,
                               1, all_tests[single_test - 1].num);
            return 0;
        }
    }
    return 1;
}