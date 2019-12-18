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
struct CMUnitTest {int dummy; } ;

/* Variables and functions */
 int cmocka_run_group_tests_name (char*,struct CMUnitTest const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct CMUnitTest const cmocka_unit_test (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_str2ld ; 

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_str2ld)
    };

    return cmocka_run_group_tests_name("str2ld", tests, NULL, NULL);
}