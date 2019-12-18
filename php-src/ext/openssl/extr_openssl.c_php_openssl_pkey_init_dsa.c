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
typedef  int /*<<< orphan*/  DSA ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_is_zero (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DSA_generate_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int DSA_set0_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_set0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_PKEY_SET_BN (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PHP_OPENSSL_RAND_ADD_TIME () ; 
 int /*<<< orphan*/  php_openssl_store_errors () ; 

__attribute__((used)) static zend_bool php_openssl_pkey_init_dsa(DSA *dsa, zval *data)
{
	BIGNUM *p, *q, *g, *priv_key, *pub_key;
	const BIGNUM *priv_key_const, *pub_key_const;

	OPENSSL_PKEY_SET_BN(data, p);
	OPENSSL_PKEY_SET_BN(data, q);
	OPENSSL_PKEY_SET_BN(data, g);
	if (!p || !q || !g || !DSA_set0_pqg(dsa, p, q, g)) {
		return 0;
	}

	OPENSSL_PKEY_SET_BN(data, pub_key);
	OPENSSL_PKEY_SET_BN(data, priv_key);
	if (pub_key) {
		return DSA_set0_key(dsa, pub_key, priv_key);
	}

	/* generate key */
	PHP_OPENSSL_RAND_ADD_TIME();
	if (!DSA_generate_key(dsa)) {
		php_openssl_store_errors();
		return 0;
	}

	/* if BN_mod_exp return -1, then DSA_generate_key succeed for failed key
	 * so we need to double check that public key is created */
	DSA_get0_key(dsa, &pub_key_const, &priv_key_const);
	if (!pub_key_const || BN_is_zero(pub_key_const)) {
		return 0;
	}
	/* all good */
	return 1;
}