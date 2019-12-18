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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int EVP_PKEY_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  X509_F_X509_CHECK_PRIVATE_KEY ; 
 int /*<<< orphan*/  X509_R_KEY_TYPE_MISMATCH ; 
 int /*<<< orphan*/  X509_R_KEY_VALUES_MISMATCH ; 
 int /*<<< orphan*/  X509_R_UNKNOWN_KEY_TYPE ; 
 int /*<<< orphan*/ * X509_get0_pubkey (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int X509_check_private_key(const X509 *x, const EVP_PKEY *k)
{
    const EVP_PKEY *xk;
    int ret;

    xk = X509_get0_pubkey(x);

    if (xk)
        ret = EVP_PKEY_cmp(xk, k);
    else
        ret = -2;

    switch (ret) {
    case 1:
        break;
    case 0:
        X509err(X509_F_X509_CHECK_PRIVATE_KEY, X509_R_KEY_VALUES_MISMATCH);
        break;
    case -1:
        X509err(X509_F_X509_CHECK_PRIVATE_KEY, X509_R_KEY_TYPE_MISMATCH);
        break;
    case -2:
        X509err(X509_F_X509_CHECK_PRIVATE_KEY, X509_R_UNKNOWN_KEY_TYPE);
    }
    if (ret > 0)
        return 1;
    return 0;
}