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
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  RSA_F4 ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_generate_key_ex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RSA_new () ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static RSA *php_openssl_tmp_rsa_cb(SSL *s, int is_export, int keylength)
{
	BIGNUM *bn = NULL;
	static RSA *rsa_tmp = NULL;

	if (!rsa_tmp && ((bn = BN_new()) == NULL)) {
		php_error_docref(NULL, E_WARNING, "allocation error generating RSA key");
	}
	if (!rsa_tmp && bn) {
		if (!BN_set_word(bn, RSA_F4) || ((rsa_tmp = RSA_new()) == NULL) ||
			!RSA_generate_key_ex(rsa_tmp, keylength, bn, NULL)) {
			if (rsa_tmp) {
				RSA_free(rsa_tmp);
			}
			rsa_tmp = NULL;
		}
		BN_free(bn);
	}

	return (rsa_tmp);
}