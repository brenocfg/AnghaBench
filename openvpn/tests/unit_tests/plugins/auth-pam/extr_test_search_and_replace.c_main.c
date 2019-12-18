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
 int /*<<< orphan*/  pass_any_empty_string__returns_null ; 
 int /*<<< orphan*/  pass_any_null_param__returns_null ; 
 int /*<<< orphan*/  pattern_not_found__returns_original ; 
 int /*<<< orphan*/  replace_longer_text__multiple_times__match_all_matches_are_replaced ; 
 int /*<<< orphan*/  replace_single_char__multiple_times__match_all_matches_are_replaced ; 
 int /*<<< orphan*/  replace_single_char__one_time__match_is_replaced ; 

int
main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(pass_any_null_param__returns_null),
        cmocka_unit_test(pass_any_empty_string__returns_null),
        cmocka_unit_test(replace_single_char__one_time__match_is_replaced),
        cmocka_unit_test(replace_single_char__multiple_times__match_all_matches_are_replaced),
        cmocka_unit_test(replace_longer_text__multiple_times__match_all_matches_are_replaced),
        cmocka_unit_test(pattern_not_found__returns_original),
    };

    return cmocka_run_group_tests_name("searchandreplace", tests, NULL, NULL);
}