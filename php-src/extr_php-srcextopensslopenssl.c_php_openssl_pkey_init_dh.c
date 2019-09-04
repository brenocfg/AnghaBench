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
typedef  int /*<<< orphan*/  DH ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  DH_generate_key (int /*<<< orphan*/ *) ; 
 int DH_set0_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_set0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_PKEY_SET_BN (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PHP_OPENSSL_RAND_ADD_TIME () ; 
 int /*<<< orphan*/ * php_openssl_dh_pub_from_priv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_openssl_store_errors () ; 

__attribute__((used)) static zend_bool php_openssl_pkey_init_dh(DH *dh, zval *data)
{
	BIGNUM *p, *q, *g, *priv_key, *pub_key;

	OPENSSL_PKEY_SET_BN(data, p);
	OPENSSL_PKEY_SET_BN(data, q);
	OPENSSL_PKEY_SET_BN(data, g);
	if (!p || !g || !DH_set0_pqg(dh, p, q, g)) {
		return 0;
	}

	OPENSSL_PKEY_SET_BN(data, priv_key);
	OPENSSL_PKEY_SET_BN(data, pub_key);
	if (pub_key) {
		return DH_set0_key(dh, pub_key, priv_key);
	}
	if (priv_key) {
		pub_key = php_openssl_dh_pub_from_priv(priv_key, g, p);
		if (pub_key == NULL) {
			return 0;
		}
		return DH_set0_key(dh, pub_key, priv_key);
	}

	/* generate key */
	PHP_OPENSSL_RAND_ADD_TIME();
	if (!DH_generate_key(dh)) {
		php_openssl_store_errors();
		return 0;
	}
	/* all good */
	return 1;
}