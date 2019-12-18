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
 struct CMUnitTest const cmocka_unit_test_setup_teardown (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_test_success ; 
 int /*<<< orphan*/  null_test_success ; 
 int /*<<< orphan*/  setup ; 
 int /*<<< orphan*/  teardown ; 

int
main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(null_test_success),
        cmocka_unit_test_setup_teardown(int_test_success, setup, teardown),
/*        cmocka_unit_test(failing_test), */
    };

    return cmocka_run_group_tests_name("success_test", tests, NULL, NULL);
}