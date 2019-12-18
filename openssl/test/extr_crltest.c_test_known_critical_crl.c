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
 int /*<<< orphan*/  X509_V_FLAG_CRL_CHECK ; 
 int /*<<< orphan*/  X509_V_OK ; 
 int /*<<< orphan*/  kKnownCriticalCRL ; 
 int /*<<< orphan*/  make_CRL_stack (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_leaf ; 
 int /*<<< orphan*/  test_root ; 
 int /*<<< orphan*/  verify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_known_critical_crl(void)
{
    X509_CRL *known_critical_crl = CRL_from_strings(kKnownCriticalCRL);
    int r;

    r = TEST_ptr(known_critical_crl)
        && TEST_int_eq(verify(test_leaf, test_root,
                              make_CRL_stack(known_critical_crl, NULL),
                              X509_V_FLAG_CRL_CHECK), X509_V_OK);
    X509_CRL_free(known_critical_crl);
    return r;
}