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
 scalar_t__ OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keygen_size ; 
 int /*<<< orphan*/  test_check_crt_components ; 
 int /*<<< orphan*/  test_check_prime_factor ; 
 int /*<<< orphan*/  test_check_prime_factor_range ; 
 int /*<<< orphan*/  test_check_private_exponent ; 
 int /*<<< orphan*/  test_check_private_key ; 
 int /*<<< orphan*/  test_check_public_exponent ; 
 int /*<<< orphan*/  test_check_public_key ; 
 int /*<<< orphan*/  test_fips1864_keygen_kat ; 
 int /*<<< orphan*/  test_invalid_keypair ; 
 int /*<<< orphan*/  test_pq_diff ; 
 int /*<<< orphan*/  test_sp80056b_keygen ; 

int setup_tests(void)
{
    ADD_TEST(test_check_public_exponent);
    ADD_TEST(test_check_prime_factor_range);
    ADD_TEST(test_check_prime_factor);
    ADD_TEST(test_check_private_exponent);
    ADD_TEST(test_check_crt_components);
    ADD_TEST(test_check_private_key);
    ADD_TEST(test_check_public_key);
    ADD_TEST(test_invalid_keypair);
    ADD_TEST(test_pq_diff);
    ADD_TEST(test_fips1864_keygen_kat);
    ADD_ALL_TESTS(test_sp80056b_keygen, (int)OSSL_NELEM(keygen_size));
    return 1;
}