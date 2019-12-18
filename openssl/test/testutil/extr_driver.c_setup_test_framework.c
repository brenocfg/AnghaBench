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
 int /*<<< orphan*/  CRYPTO_MEM_CHECK_ON ; 
 int /*<<< orphan*/  CRYPTO_mem_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_set_mem_debug (int) ; 
 int atoi (char*) ; 
 char** copy_argv (int*,char**) ; 
 char* getenv (char*) ; 
 int level ; 
 int /*<<< orphan*/  opt_init (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_seed (int) ; 
 scalar_t__ should_report_leaks () ; 
 int /*<<< orphan*/  test_get_options () ; 
 int /*<<< orphan*/  win32_utf8argv (int*,char***) ; 

int setup_test_framework(int argc, char *argv[])
{
    char *test_seed = getenv("OPENSSL_TEST_RAND_ORDER");
    char *TAP_levels = getenv("HARNESS_OSSL_LEVEL");

    if (TAP_levels != NULL)
        level = 4 * atoi(TAP_levels);
    if (test_seed != NULL)
        set_seed(atoi(test_seed));

#ifndef OPENSSL_NO_CRYPTO_MDEBUG
    if (should_report_leaks()) {
        CRYPTO_set_mem_debug(1);
        CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON);
    }
#endif

#if defined(OPENSSL_SYS_VMS) && defined(__DECC)
    argv = copy_argv(&argc, argv);
#elif defined(_WIN32)
    /*
     * Replace argv[] with UTF-8 encoded strings.
     */
    win32_utf8argv(&argc, &argv);
#endif

    if (!opt_init(argc, argv, test_get_options()))
        return 0;
    return 1;
}