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
 int /*<<< orphan*/  OpenSSL_add_all_algorithms () ; 
 int /*<<< orphan*/  auth_token_basic_test ; 
 int /*<<< orphan*/  auth_token_fail_invalid_key ; 
 int /*<<< orphan*/  auth_token_test_empty_user ; 
 int /*<<< orphan*/  auth_token_test_env ; 
 int /*<<< orphan*/  auth_token_test_key_load ; 
 int /*<<< orphan*/  auth_token_test_known_keys ; 
 int /*<<< orphan*/  auth_token_test_random_keys ; 
 int /*<<< orphan*/  auth_token_test_timeout ; 
 int cmocka_run_group_tests_name (char*,struct CMUnitTest const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct CMUnitTest const cmocka_unit_test_setup_teardown (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup ; 
 int /*<<< orphan*/  teardown ; 

int
main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(auth_token_basic_test, setup, teardown),
        cmocka_unit_test_setup_teardown(auth_token_fail_invalid_key, setup, teardown),
        cmocka_unit_test_setup_teardown(auth_token_test_known_keys, setup, teardown),
        cmocka_unit_test_setup_teardown(auth_token_test_empty_user, setup, teardown),
        cmocka_unit_test_setup_teardown(auth_token_test_env, setup, teardown),
        cmocka_unit_test_setup_teardown(auth_token_test_random_keys, setup, teardown),
        cmocka_unit_test_setup_teardown(auth_token_test_key_load, setup, teardown),
        cmocka_unit_test_setup_teardown(auth_token_test_timeout, setup, teardown),
    };

#if defined(ENABLE_CRYPTO_OPENSSL)
    OpenSSL_add_all_algorithms();
#endif

    int ret = cmocka_run_group_tests_name("auth-token tests", tests, NULL, NULL);

    return ret;
}