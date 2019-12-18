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
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  const* EVP_aes_128_cbc () ; 
 int /*<<< orphan*/  const* EVP_aes_192_cbc () ; 
 int /*<<< orphan*/  const* EVP_aes_256_cbc () ; 
 int /*<<< orphan*/  const* EVP_des_cbc () ; 
 int /*<<< orphan*/  const* EVP_des_ede3_cbc () ; 
 int /*<<< orphan*/  const* EVP_rc2_40_cbc () ; 
 int /*<<< orphan*/  const* EVP_rc2_64_cbc () ; 
 int /*<<< orphan*/  const* EVP_rc2_cbc () ; 
#define  PHP_OPENSSL_CIPHER_3DES 135 
#define  PHP_OPENSSL_CIPHER_AES_128_CBC 134 
#define  PHP_OPENSSL_CIPHER_AES_192_CBC 133 
#define  PHP_OPENSSL_CIPHER_AES_256_CBC 132 
#define  PHP_OPENSSL_CIPHER_DES 131 
#define  PHP_OPENSSL_CIPHER_RC2_128 130 
#define  PHP_OPENSSL_CIPHER_RC2_40 129 
#define  PHP_OPENSSL_CIPHER_RC2_64 128 

__attribute__((used)) static const EVP_CIPHER * php_openssl_get_evp_cipher_from_algo(zend_long algo) { /* {{{ */
	switch (algo) {
#ifndef OPENSSL_NO_RC2
		case PHP_OPENSSL_CIPHER_RC2_40:
			return EVP_rc2_40_cbc();
			break;
		case PHP_OPENSSL_CIPHER_RC2_64:
			return EVP_rc2_64_cbc();
			break;
		case PHP_OPENSSL_CIPHER_RC2_128:
			return EVP_rc2_cbc();
			break;
#endif

#ifndef OPENSSL_NO_DES
		case PHP_OPENSSL_CIPHER_DES:
			return EVP_des_cbc();
			break;
		case PHP_OPENSSL_CIPHER_3DES:
			return EVP_des_ede3_cbc();
			break;
#endif

#ifndef OPENSSL_NO_AES
		case PHP_OPENSSL_CIPHER_AES_128_CBC:
			return EVP_aes_128_cbc();
			break;
		case PHP_OPENSSL_CIPHER_AES_192_CBC:
			return EVP_aes_192_cbc();
			break;
		case PHP_OPENSSL_CIPHER_AES_256_CBC:
			return EVP_aes_256_cbc();
			break;
#endif


		default:
			return NULL;
			break;
	}
}