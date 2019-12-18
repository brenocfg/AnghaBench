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
 int EC_get_builtin_curves (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * OPENSSL_malloc (int) ; 
 int OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_note (char*) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int) ; 
 int crv_len ; 
 int /*<<< orphan*/ * curves ; 
 int /*<<< orphan*/  ecdsa_cavs_kats ; 
 int /*<<< orphan*/  test_builtin ; 
 int /*<<< orphan*/  x9_62_tests ; 

int setup_tests(void)
{
#ifdef OPENSSL_NO_EC
    TEST_note("Elliptic curves are disabled.");
#else
    /* get a list of all internal curves */
    crv_len = EC_get_builtin_curves(NULL, 0);
    if (!TEST_ptr(curves = OPENSSL_malloc(sizeof(*curves) * crv_len))
        || !TEST_true(EC_get_builtin_curves(curves, crv_len)))
        return 0;
    ADD_ALL_TESTS(test_builtin, crv_len);
    ADD_ALL_TESTS(x9_62_tests, OSSL_NELEM(ecdsa_cavs_kats));
#endif
    return 1;
}