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
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_CTX_new () ; 
 int OPT_EOF ; 
#define  OPT_ERR 130 
#define  OPT_STOCHASTIC_TESTS 129 
#define  OPT_TEST_CASES 128 
 scalar_t__ OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  kMPITests ; 
 int /*<<< orphan*/  not_primes ; 
 int opt_next () ; 
 int /*<<< orphan*/  primes ; 
 int /*<<< orphan*/  run_file_tests ; 
 int /*<<< orphan*/  test_asc2bn ; 
 int /*<<< orphan*/  test_badmod ; 
 int /*<<< orphan*/  test_bn2padded ; 
 int /*<<< orphan*/  test_ctx_consttime_flag ; 
 int /*<<< orphan*/  test_dec2bn ; 
 int /*<<< orphan*/  test_div_recip ; 
 int /*<<< orphan*/  test_expmodone ; 
 int /*<<< orphan*/  test_expmodzero ; 
 int /*<<< orphan*/  test_gcd_prime ; 
 int test_get_argument_count () ; 
 int /*<<< orphan*/  test_gf2m_add ; 
 int /*<<< orphan*/  test_gf2m_mod ; 
 int /*<<< orphan*/  test_gf2m_moddiv ; 
 int /*<<< orphan*/  test_gf2m_modexp ; 
 int /*<<< orphan*/  test_gf2m_modinv ; 
 int /*<<< orphan*/  test_gf2m_modsolvequad ; 
 int /*<<< orphan*/  test_gf2m_modsqrt ; 
 int /*<<< orphan*/  test_gf2m_mul ; 
 int /*<<< orphan*/  test_gf2m_sqr ; 
 int /*<<< orphan*/  test_hex2bn ; 
 int /*<<< orphan*/  test_is_prime ; 
 int /*<<< orphan*/  test_kronecker ; 
 int /*<<< orphan*/  test_mod ; 
 int /*<<< orphan*/  test_modexp_mont5 ; 
 int /*<<< orphan*/  test_mpi ; 
 int /*<<< orphan*/  test_negzero ; 
 int /*<<< orphan*/  test_not_prime ; 
 int /*<<< orphan*/  test_rand ; 
 int /*<<< orphan*/  test_rand_range ; 
 int /*<<< orphan*/  test_smallprime ; 
 int /*<<< orphan*/  test_smallsafeprime ; 
 int /*<<< orphan*/  test_sub ; 
 int /*<<< orphan*/  test_swap ; 

int setup_tests(void)
{
    OPTION_CHOICE o;
    int n, stochastic = 0;

    while ((o = opt_next()) != OPT_EOF) {
        switch (o) {
        case OPT_STOCHASTIC_TESTS:
            stochastic = 1;
            break;
        case OPT_TEST_CASES:
           break;
        default:
        case OPT_ERR:
            return 0;
        }
    }
    n  = test_get_argument_count();

    if (!TEST_ptr(ctx = BN_CTX_new()))
        return 0;

    if (n == 0) {
        ADD_TEST(test_sub);
        ADD_TEST(test_div_recip);
        ADD_TEST(test_mod);
        ADD_TEST(test_modexp_mont5);
        ADD_TEST(test_kronecker);
        ADD_TEST(test_rand);
        ADD_TEST(test_bn2padded);
        ADD_TEST(test_dec2bn);
        ADD_TEST(test_hex2bn);
        ADD_TEST(test_asc2bn);
        ADD_ALL_TESTS(test_mpi, (int)OSSL_NELEM(kMPITests));
        ADD_TEST(test_negzero);
        ADD_TEST(test_badmod);
        ADD_TEST(test_expmodzero);
        ADD_TEST(test_expmodone);
        ADD_ALL_TESTS(test_smallprime, 16);
        ADD_ALL_TESTS(test_smallsafeprime, 16);
        ADD_TEST(test_swap);
        ADD_TEST(test_ctx_consttime_flag);
#ifndef OPENSSL_NO_EC2M
        ADD_TEST(test_gf2m_add);
        ADD_TEST(test_gf2m_mod);
        ADD_TEST(test_gf2m_mul);
        ADD_TEST(test_gf2m_sqr);
        ADD_TEST(test_gf2m_modinv);
        ADD_TEST(test_gf2m_moddiv);
        ADD_TEST(test_gf2m_modexp);
        ADD_TEST(test_gf2m_modsqrt);
        ADD_TEST(test_gf2m_modsolvequad);
#endif
        ADD_ALL_TESTS(test_is_prime, (int)OSSL_NELEM(primes));
        ADD_ALL_TESTS(test_not_prime, (int)OSSL_NELEM(not_primes));
        ADD_TEST(test_gcd_prime);
        if (stochastic)
            ADD_TEST(test_rand_range);
    } else {
        ADD_ALL_TESTS(run_file_tests, n);
    }
    return 1;
}