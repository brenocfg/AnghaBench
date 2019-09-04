#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* test_case_name; int (* test_fn ) () ;int num; } ;

/* Variables and functions */
 size_t OSSL_NELEM (TYPE_1__*) ; 
 TYPE_1__* all_tests ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  num_test_cases ; 
 size_t num_tests ; 

void add_test(const char *test_case_name, int (*test_fn) (void))
{
    assert(num_tests != OSSL_NELEM(all_tests));
    all_tests[num_tests].test_case_name = test_case_name;
    all_tests[num_tests].test_fn = test_fn;
    all_tests[num_tests].num = -1;
    ++num_tests;
    ++num_test_cases;
}