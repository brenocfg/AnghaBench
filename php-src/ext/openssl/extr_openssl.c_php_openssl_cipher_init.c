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
typedef  int zend_long ;
typedef  int zend_bool ;
struct php_openssl_cipher_mode {int /*<<< orphan*/  aead_set_tag_flag; int /*<<< orphan*/  is_aead; scalar_t__ is_single_run_aead; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_CTX_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned char*) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_set_key_length (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_set_padding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t EVP_CIPHER_iv_length (int /*<<< orphan*/  const*) ; 
 int EVP_CIPHER_key_length (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
 int OPENSSL_DONT_ZERO_PAD_KEY ; 
 int OPENSSL_ZERO_PADDING ; 
 int SUCCESS ; 
 unsigned char* emalloc (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  php_openssl_store_errors () ; 
 int php_openssl_validate_iv (char**,size_t*,size_t,int*,int /*<<< orphan*/ *,struct php_openssl_cipher_mode*) ; 

__attribute__((used)) static int php_openssl_cipher_init(const EVP_CIPHER *cipher_type,
		EVP_CIPHER_CTX *cipher_ctx, struct php_openssl_cipher_mode *mode,
		char **ppassword, size_t *ppassword_len, zend_bool *free_password,
		char **piv, size_t *piv_len, zend_bool *free_iv,
		char *tag, int tag_len, zend_long options, int enc)  /* {{{ */
{
	unsigned char *key;
	int key_len, password_len;
	size_t max_iv_len;

	*free_password = 0;

	max_iv_len = EVP_CIPHER_iv_length(cipher_type);
	if (enc && *piv_len == 0 && max_iv_len > 0 && !mode->is_aead) {
		php_error_docref(NULL, E_WARNING,
				"Using an empty Initialization Vector (iv) is potentially insecure and not recommended");
	}

	if (!EVP_CipherInit_ex(cipher_ctx, cipher_type, NULL, NULL, NULL, enc)) {
		php_openssl_store_errors();
		return FAILURE;
	}
	if (php_openssl_validate_iv(piv, piv_len, max_iv_len, free_iv, cipher_ctx, mode) == FAILURE) {
		return FAILURE;
	}
	if (mode->is_single_run_aead && enc) {
		if (!EVP_CIPHER_CTX_ctrl(cipher_ctx, mode->aead_set_tag_flag, tag_len, NULL)) {
			php_error_docref(NULL, E_WARNING, "Setting tag length for AEAD cipher failed");
			return FAILURE;
		}
	} else if (!enc && tag && tag_len > 0) {
		if (!mode->is_aead) {
			php_error_docref(NULL, E_WARNING, "The tag cannot be used because the cipher method does not support AEAD");
		} else if (!EVP_CIPHER_CTX_ctrl(cipher_ctx, mode->aead_set_tag_flag, tag_len, (unsigned char *) tag)) {
			php_error_docref(NULL, E_WARNING, "Setting tag for AEAD cipher decryption failed");
			return FAILURE;
		}
	}
	/* check and set key */
	password_len = (int) *ppassword_len;
	key_len = EVP_CIPHER_key_length(cipher_type);
	if (key_len > password_len) {
		if ((OPENSSL_DONT_ZERO_PAD_KEY & options) && !EVP_CIPHER_CTX_set_key_length(cipher_ctx, password_len)) {
			php_openssl_store_errors();
			php_error_docref(NULL, E_WARNING, "Key length cannot be set for the cipher method");
			return FAILURE;
		}
		key = emalloc(key_len);
		memset(key, 0, key_len);
		memcpy(key, *ppassword, password_len);
		*ppassword = (char *) key;
		*ppassword_len = key_len;
		*free_password = 1;
	} else {
		if (password_len > key_len && !EVP_CIPHER_CTX_set_key_length(cipher_ctx, password_len)) {
			php_openssl_store_errors();
		}
		key = (unsigned char*)*ppassword;
	}

	if (!EVP_CipherInit_ex(cipher_ctx, NULL, NULL, key, (unsigned char *)*piv, enc)) {
		php_openssl_store_errors();
		return FAILURE;
	}
	if (options & OPENSSL_ZERO_PADDING) {
		EVP_CIPHER_CTX_set_padding(cipher_ctx, 0);
	}

	return SUCCESS;
}