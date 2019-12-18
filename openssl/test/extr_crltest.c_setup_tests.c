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
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_from_strings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kCRLTestLeaf ; 
 int /*<<< orphan*/  kCRLTestRoot ; 
 int /*<<< orphan*/  test_bad_issuer_crl ; 
 int /*<<< orphan*/  test_basic_crl ; 
 int /*<<< orphan*/  test_known_critical_crl ; 
 int /*<<< orphan*/  test_leaf ; 
 int /*<<< orphan*/  test_no_crl ; 
 int /*<<< orphan*/  test_reuse_crl ; 
 int /*<<< orphan*/  test_root ; 
 int /*<<< orphan*/  test_unknown_critical_crl ; 
 int /*<<< orphan*/  unknown_critical_crls ; 

int setup_tests(void)
{
    if (!TEST_ptr(test_root = X509_from_strings(kCRLTestRoot))
        || !TEST_ptr(test_leaf = X509_from_strings(kCRLTestLeaf)))
        return 0;

    ADD_TEST(test_no_crl);
    ADD_TEST(test_basic_crl);
    ADD_TEST(test_bad_issuer_crl);
    ADD_TEST(test_known_critical_crl);
    ADD_ALL_TESTS(test_unknown_critical_crl, OSSL_NELEM(unknown_critical_crls));
    ADD_TEST(test_reuse_crl);
    return 1;
}