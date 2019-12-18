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
 int /*<<< orphan*/  argv_insert_head__non_empty_argv__head_added ; 
 int /*<<< orphan*/  argv_parse_cmd__command_and_extra_options__argc_correct ; 
 int /*<<< orphan*/  argv_parse_cmd__command_string__argc_correct ; 
 int /*<<< orphan*/  argv_printf__combined_path_with_spaces__argc_correct ; 
 int /*<<< orphan*/  argv_printf__multiple_spaces_in_format__parsed_as_one ; 
 int /*<<< orphan*/  argv_printf_cat__multiple_spaces_in_format__parsed_as_one ; 
 int /*<<< orphan*/  argv_printf_cat__used_twice__argc_correct ; 
 int /*<<< orphan*/  argv_str__multiple_argv__correct_output ; 
 int cmocka_run_group_tests_name (char*,struct CMUnitTest const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct CMUnitTest const cmocka_unit_test (int /*<<< orphan*/ ) ; 

int
main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(argv_printf__multiple_spaces_in_format__parsed_as_one),
        cmocka_unit_test(argv_printf_cat__multiple_spaces_in_format__parsed_as_one),
        cmocka_unit_test(argv_printf__combined_path_with_spaces__argc_correct),
        cmocka_unit_test(argv_parse_cmd__command_string__argc_correct),
        cmocka_unit_test(argv_parse_cmd__command_and_extra_options__argc_correct),
        cmocka_unit_test(argv_printf_cat__used_twice__argc_correct),
        cmocka_unit_test(argv_str__multiple_argv__correct_output),
        cmocka_unit_test(argv_insert_head__non_empty_argv__head_added),
    };

    return cmocka_run_group_tests_name("argv", tests, NULL, NULL);
}