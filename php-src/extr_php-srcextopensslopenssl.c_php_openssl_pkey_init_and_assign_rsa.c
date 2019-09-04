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
typedef  int /*<<< orphan*/  zval ;
typedef  int zend_bool ;
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_assign_RSA (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_PKEY_SET_BN (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_set0_crt_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_set0_factors (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_set0_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_openssl_store_errors () ; 

__attribute__((used)) static zend_bool php_openssl_pkey_init_and_assign_rsa(EVP_PKEY *pkey, RSA *rsa, zval *data)
{
	BIGNUM *n, *e, *d, *p, *q, *dmp1, *dmq1, *iqmp;

	OPENSSL_PKEY_SET_BN(data, n);
	OPENSSL_PKEY_SET_BN(data, e);
	OPENSSL_PKEY_SET_BN(data, d);
	if (!n || !d || !RSA_set0_key(rsa, n, e, d)) {
		return 0;
	}

	OPENSSL_PKEY_SET_BN(data, p);
	OPENSSL_PKEY_SET_BN(data, q);
	if ((p || q) && !RSA_set0_factors(rsa, p, q)) {
		return 0;
	}

	OPENSSL_PKEY_SET_BN(data, dmp1);
	OPENSSL_PKEY_SET_BN(data, dmq1);
	OPENSSL_PKEY_SET_BN(data, iqmp);
	if ((dmp1 || dmq1 || iqmp) && !RSA_set0_crt_params(rsa, dmp1, dmq1, iqmp)) {
		return 0;
	}

	if (!EVP_PKEY_assign_RSA(pkey, rsa)) {
		php_openssl_store_errors();
		return 0;
	}

	return 1;
}