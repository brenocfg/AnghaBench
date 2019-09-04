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
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  cleanup_tests () ; 
 int /*<<< orphan*/  global_init () ; 
 int /*<<< orphan*/  opt_check_usage () ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 int pulldown_test_framework (int) ; 
 int run_tests (char*) ; 
 int /*<<< orphan*/  setup_test_framework (int,char**) ; 
 scalar_t__ setup_tests () ; 
 int /*<<< orphan*/  test_close_streams () ; 
 int /*<<< orphan*/  test_get_options () ; 
 int /*<<< orphan*/  test_open_streams () ; 
 int /*<<< orphan*/  test_printf_stderr (char*) ; 

int main(int argc, char *argv[])
{
    int ret = EXIT_FAILURE;

    test_open_streams();

    if (!global_init()) {
        test_printf_stderr("Global init failed - aborting\n");
        return ret;
    }

    if (!setup_test_framework(argc, argv))
        goto end;

    if (setup_tests()) {
        ret = run_tests(argv[0]);
        cleanup_tests();
        opt_check_usage();
    } else {
        opt_help(test_get_options());
    }
end:
    ret = pulldown_test_framework(ret);
    test_close_streams();
    return ret;
}