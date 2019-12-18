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
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  DSA ;
typedef  int /*<<< orphan*/  DH ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  DH_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  DH_get0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  DSA_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  DSA_get0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/ * EC_KEY_get0_private_key (int /*<<< orphan*/ *) ; 
#define  EVP_PKEY_DH 136 
#define  EVP_PKEY_DSA 135 
#define  EVP_PKEY_DSA1 134 
#define  EVP_PKEY_DSA2 133 
#define  EVP_PKEY_DSA3 132 
#define  EVP_PKEY_DSA4 131 
#define  EVP_PKEY_EC 130 
#define  EVP_PKEY_RSA 129 
#define  EVP_PKEY_RSA2 128 
 int /*<<< orphan*/ * EVP_PKEY_get0_DH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get0_DSA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get0_EC_KEY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get0_RSA (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  RSA_get0_factors (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int php_openssl_is_private_key(EVP_PKEY* pkey)
{
	assert(pkey != NULL);

	switch (EVP_PKEY_id(pkey)) {
		case EVP_PKEY_RSA:
		case EVP_PKEY_RSA2:
			{
				RSA *rsa = EVP_PKEY_get0_RSA(pkey);
				if (rsa != NULL) {
					const BIGNUM *p, *q;

					RSA_get0_factors(rsa, &p, &q);
					 if (p == NULL || q == NULL) {
						return 0;
					 }
				}
			}
			break;
		case EVP_PKEY_DSA:
		case EVP_PKEY_DSA1:
		case EVP_PKEY_DSA2:
		case EVP_PKEY_DSA3:
		case EVP_PKEY_DSA4:
			{
				DSA *dsa = EVP_PKEY_get0_DSA(pkey);
				if (dsa != NULL) {
					const BIGNUM *p, *q, *g, *pub_key, *priv_key;

					DSA_get0_pqg(dsa, &p, &q, &g);
					if (p == NULL || q == NULL) {
						return 0;
					}

					DSA_get0_key(dsa, &pub_key, &priv_key);
					if (priv_key == NULL) {
						return 0;
					}
				}
			}
			break;
		case EVP_PKEY_DH:
			{
				DH *dh = EVP_PKEY_get0_DH(pkey);
				if (dh != NULL) {
					const BIGNUM *p, *q, *g, *pub_key, *priv_key;

					DH_get0_pqg(dh, &p, &q, &g);
					if (p == NULL) {
						return 0;
					}

					DH_get0_key(dh, &pub_key, &priv_key);
					if (priv_key == NULL) {
						return 0;
					}
				}
			}
			break;
#ifdef HAVE_EVP_PKEY_EC
		case EVP_PKEY_EC:
			{
				EC_KEY *ec = EVP_PKEY_get0_EC_KEY(pkey);
				if (ec != NULL && NULL == EC_KEY_get0_private_key(ec)) {
					return 0;
				}
			}
			break;
#endif
		default:
			php_error_docref(NULL, E_WARNING, "key type not supported in this PHP build!");
			break;
	}
	return 1;
}