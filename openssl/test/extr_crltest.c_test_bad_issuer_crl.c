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
typedef  int /*<<< orphan*/  X509_CRL ;

/* Variables and functions */
 int /*<<< orphan*/ * CRL_from_strings (int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_CRL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_V_ERR_UNABLE_TO_GET_CRL ; 
 int /*<<< orphan*/  X509_V_FLAG_CRL_CHECK ; 
 int /*<<< orphan*/  kBadIssuerCRL ; 
 int /*<<< orphan*/  make_CRL_stack (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_leaf ; 
 int /*<<< orphan*/  test_root ; 
 int /*<<< orphan*/  verify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_bad_issuer_crl(void)
{
    X509_CRL *bad_issuer_crl = CRL_from_strings(kBadIssuerCRL);
    int r;

    r = TEST_ptr(bad_issuer_crl)
        && TEST_int_eq(verify(test_leaf, test_root,
                              make_CRL_stack(bad_issuer_crl, NULL),
                              X509_V_FLAG_CRL_CHECK),
                       X509_V_ERR_UNABLE_TO_GET_CRL);
    X509_CRL_free(bad_issuer_crl);
    return r;
}