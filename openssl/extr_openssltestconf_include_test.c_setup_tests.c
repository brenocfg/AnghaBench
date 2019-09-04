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
typedef  int OPTION_CHOICE ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 char* BIO_new_file (char const*,char*) ; 
 char* NCONF_new (int /*<<< orphan*/ *) ; 
 int OPT_EOF ; 
#define  OPT_FAIL 129 
#define  OPT_TEST_CASES 128 
 int /*<<< orphan*/  TEST_note (char*) ; 
 int /*<<< orphan*/  TEST_ptr (char const*) ; 
 int /*<<< orphan*/  change_path (char const*) ; 
 char const* conf ; 
 int expect_failure ; 
 char const* in ; 
 int opt_next () ; 
 int /*<<< orphan*/  test_check_null_numbers ; 
 int /*<<< orphan*/  test_check_overflow ; 
 char* test_get_argument (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_load_config ; 

int setup_tests(void)
{
    const char *conf_file;
    OPTION_CHOICE o;

    if (!TEST_ptr(conf = NCONF_new(NULL)))
        return 0;

    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_FAIL:
            expect_failure = 1;
            break;
        case OPT_TEST_CASES:
            break;
        default:
            return 0;
        }
    }

    conf_file = test_get_argument(0);
    if (!TEST_ptr(conf_file)
        || !TEST_ptr(in = BIO_new_file(conf_file, "r"))) {
        TEST_note("Unable to open the file argument");
        return 0;
    }

    /*
     * For this test we need to chdir as we use relative
     * path names in the config files.
     */
    change_path(conf_file);

    ADD_TEST(test_load_config);
    ADD_TEST(test_check_null_numbers);
    ADD_TEST(test_check_overflow);
    return 1;
}