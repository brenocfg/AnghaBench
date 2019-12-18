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
typedef  int /*<<< orphan*/  TEST_RC4_KEY ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_meth_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_meth_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_do_cipher (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_impl_ctx_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_iv_length (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPH_VARIABLE_LENGTH ; 
 int /*<<< orphan*/  NID_rc4 ; 
 int /*<<< orphan*/  TEST_RC4_KEY_SIZE ; 
 int /*<<< orphan*/  const* r4_cipher ; 
 int /*<<< orphan*/  test_rc4_cipher ; 
 int /*<<< orphan*/  test_rc4_init_key ; 

__attribute__((used)) static const EVP_CIPHER *test_r4_cipher(void)
{
    if (r4_cipher == NULL) {
        EVP_CIPHER *cipher;

        if ((cipher = EVP_CIPHER_meth_new(NID_rc4, 1, TEST_RC4_KEY_SIZE)) == NULL
            || !EVP_CIPHER_meth_set_iv_length(cipher, 0)
            || !EVP_CIPHER_meth_set_flags(cipher, EVP_CIPH_VARIABLE_LENGTH)
            || !EVP_CIPHER_meth_set_init(cipher, test_rc4_init_key)
            || !EVP_CIPHER_meth_set_do_cipher(cipher, test_rc4_cipher)
            || !EVP_CIPHER_meth_set_impl_ctx_size(cipher, sizeof(TEST_RC4_KEY))) {
            EVP_CIPHER_meth_free(cipher);
            cipher = NULL;
        }
        r4_cipher = cipher;
    }
    return r4_cipher;
}