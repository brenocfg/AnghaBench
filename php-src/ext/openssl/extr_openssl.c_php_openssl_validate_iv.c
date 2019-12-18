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
typedef  int zend_bool ;
struct php_openssl_cipher_mode {int /*<<< orphan*/  aead_ivlen_flag; scalar_t__ is_aead; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int EVP_CIPHER_CTX_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
 int SUCCESS ; 
 char* ecalloc (int,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int php_openssl_validate_iv(char **piv, size_t *piv_len, size_t iv_required_len,
		zend_bool *free_iv, EVP_CIPHER_CTX *cipher_ctx, struct php_openssl_cipher_mode *mode) /* {{{ */
{
	char *iv_new;

	/* Best case scenario, user behaved */
	if (*piv_len == iv_required_len) {
		return SUCCESS;
	}

	if (mode->is_aead) {
		if (EVP_CIPHER_CTX_ctrl(cipher_ctx, mode->aead_ivlen_flag, *piv_len, NULL) != 1) {
			php_error_docref(NULL, E_WARNING, "Setting of IV length for AEAD mode failed");
			return FAILURE;
		}
		return SUCCESS;
	}

	iv_new = ecalloc(1, iv_required_len + 1);

	if (*piv_len == 0) {
		/* BC behavior */
		*piv_len = iv_required_len;
		*piv = iv_new;
		*free_iv = 1;
		return SUCCESS;

	}

	if (*piv_len < iv_required_len) {
		php_error_docref(NULL, E_WARNING,
				"IV passed is only %zd bytes long, cipher expects an IV of precisely %zd bytes, padding with \\0",
				*piv_len, iv_required_len);
		memcpy(iv_new, *piv, *piv_len);
		*piv_len = iv_required_len;
		*piv = iv_new;
		*free_iv = 1;
		return SUCCESS;
	}

	php_error_docref(NULL, E_WARNING,
			"IV passed is %zd bytes long which is longer than the %zd expected by selected cipher, truncating",
			*piv_len, iv_required_len);
	memcpy(iv_new, *piv, iv_required_len);
	*piv_len = iv_required_len;
	*piv = iv_new;
	*free_iv = 1;
	return SUCCESS;

}