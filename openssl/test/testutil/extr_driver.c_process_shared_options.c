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
typedef  int OPTION_CHOICE_DEFAULT ;

/* Variables and functions */
 int OPT_EOF ; 
#define  OPT_ERR 134 
#define  OPT_TEST_HELP 133 
#define  OPT_TEST_INDENT 132 
#define  OPT_TEST_ITERATION 131 
#define  OPT_TEST_LIST 130 
#define  OPT_TEST_SEED 129 
#define  OPT_TEST_SINGLE 128 
 int /*<<< orphan*/  check_single_test_params (char*,char*,char*) ; 
 int level ; 
 char* opt_arg () ; 
 int /*<<< orphan*/  opt_begin () ; 
 char* opt_flag () ; 
 int /*<<< orphan*/  opt_help (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_int (char*,int*) ; 
 int opt_next () ; 
 int /*<<< orphan*/  set_seed (int) ; 
 int show_list ; 
 int single_iter ; 
 int /*<<< orphan*/  test_get_options () ; 

__attribute__((used)) static int process_shared_options(void)
{
    OPTION_CHOICE_DEFAULT o;
    int value;
    int ret = -1;
    char *flag_test = "";
    char *flag_iter = "";
    char *testname = NULL;

    opt_begin();
    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        /* Ignore any test options at this level */
        default:
            break;
        case OPT_ERR:
            return ret;
        case OPT_TEST_HELP:
            opt_help(test_get_options());
            return 0;
        case OPT_TEST_LIST:
            show_list = 1;
            break;
        case OPT_TEST_SINGLE:
            flag_test = opt_flag();
            testname = opt_arg();
            break;
        case OPT_TEST_ITERATION:
            flag_iter = opt_flag();
            if (!opt_int(opt_arg(), &single_iter))
                goto end;
            break;
        case OPT_TEST_INDENT:
            if (!opt_int(opt_arg(), &value))
                goto end;
            level = 4 * value;
            break;
        case OPT_TEST_SEED:
            if (!opt_int(opt_arg(), &value))
                goto end;
            set_seed(value);
            break;
        }
    }
    if (!check_single_test_params(testname, flag_test, flag_iter))
        goto end;
    ret = 1;
end:
    return ret;
}