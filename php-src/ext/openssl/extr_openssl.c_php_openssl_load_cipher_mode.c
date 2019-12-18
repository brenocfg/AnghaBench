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
struct php_openssl_cipher_mode {int is_aead; int is_single_run_aead; int /*<<< orphan*/  aead_ivlen_flag; int /*<<< orphan*/  aead_set_tag_flag; int /*<<< orphan*/  aead_get_tag_flag; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int EVP_CIPHER_mode (int /*<<< orphan*/  const*) ; 
#define  EVP_CIPH_CCM_MODE 129 
#define  EVP_CIPH_GCM_MODE 128 
 int /*<<< orphan*/  EVP_CTRL_CCM_GET_TAG ; 
 int /*<<< orphan*/  EVP_CTRL_CCM_SET_IVLEN ; 
 int /*<<< orphan*/  EVP_CTRL_CCM_SET_TAG ; 
 int /*<<< orphan*/  EVP_CTRL_GCM_GET_TAG ; 
 int /*<<< orphan*/  EVP_CTRL_GCM_SET_IVLEN ; 
 int /*<<< orphan*/  EVP_CTRL_GCM_SET_TAG ; 
 int /*<<< orphan*/  memset (struct php_openssl_cipher_mode*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void php_openssl_load_cipher_mode(struct php_openssl_cipher_mode *mode, const EVP_CIPHER *cipher_type) /* {{{ */
{
	switch (EVP_CIPHER_mode(cipher_type)) {
#ifdef EVP_CIPH_GCM_MODE
		case EVP_CIPH_GCM_MODE:
			mode->is_aead = 1;
			mode->is_single_run_aead = 0;
			mode->aead_get_tag_flag = EVP_CTRL_GCM_GET_TAG;
			mode->aead_set_tag_flag = EVP_CTRL_GCM_SET_TAG;
			mode->aead_ivlen_flag = EVP_CTRL_GCM_SET_IVLEN;
			break;
#endif
#ifdef EVP_CIPH_CCM_MODE
		case EVP_CIPH_CCM_MODE:
			mode->is_aead = 1;
			mode->is_single_run_aead = 1;
			mode->aead_get_tag_flag = EVP_CTRL_CCM_GET_TAG;
			mode->aead_set_tag_flag = EVP_CTRL_CCM_SET_TAG;
			mode->aead_ivlen_flag = EVP_CTRL_CCM_SET_IVLEN;
			break;
#endif
		default:
			memset(mode, 0, sizeof(struct php_openssl_cipher_mode));
	}
}