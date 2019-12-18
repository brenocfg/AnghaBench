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
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAND_DRBG_get_ex_new_index (long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  app_data_index ; 
 int crngt_num_cases ; 
 int /*<<< orphan*/  drbg_test ; 
 int /*<<< orphan*/  drgb_types ; 
 int /*<<< orphan*/  test_crngt ; 
 int /*<<< orphan*/  test_error_checks ; 
 int /*<<< orphan*/  test_kats ; 
 int /*<<< orphan*/  test_multi_set ; 
 int /*<<< orphan*/  test_multi_thread ; 
 int /*<<< orphan*/  test_rand_add ; 
 int /*<<< orphan*/  test_rand_drbg_prediction_resistance ; 
 int /*<<< orphan*/  test_rand_drbg_reseed ; 
 int /*<<< orphan*/  test_rand_seed ; 
 int /*<<< orphan*/  test_set_defaults ; 

int setup_tests(void)
{
    app_data_index = RAND_DRBG_get_ex_new_index(0L, NULL, NULL, NULL, NULL);

    ADD_ALL_TESTS(test_kats, OSSL_NELEM(drbg_test));
    ADD_ALL_TESTS(test_error_checks, OSSL_NELEM(drbg_test));
    ADD_TEST(test_rand_drbg_reseed);
    ADD_TEST(test_rand_seed);
    ADD_TEST(test_rand_add);
    ADD_TEST(test_rand_drbg_prediction_resistance);
    ADD_TEST(test_multi_set);
    ADD_TEST(test_set_defaults);
#if defined(OPENSSL_THREADS)
    ADD_TEST(test_multi_thread);
#endif
    ADD_ALL_TESTS(test_crngt, crngt_num_cases * OSSL_NELEM(drgb_types));
    return 1;
}