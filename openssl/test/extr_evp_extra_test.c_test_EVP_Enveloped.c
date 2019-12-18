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
typedef  int /*<<< orphan*/  msg ;
typedef  unsigned char EVP_PKEY ;
typedef  unsigned char EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (unsigned char*) ; 
 unsigned char* EVP_CIPHER_CTX_new () ; 
 int EVP_MAX_IV_LENGTH ; 
 int /*<<< orphan*/  EVP_OpenFinal (unsigned char*,unsigned char*,int*) ; 
 int /*<<< orphan*/  EVP_OpenInit (unsigned char*,int /*<<< orphan*/  const*,unsigned char*,int,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  EVP_OpenUpdate (unsigned char*,unsigned char*,int*,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_PKEY_free (unsigned char*) ; 
 int /*<<< orphan*/  EVP_PKEY_size (unsigned char*) ; 
 int /*<<< orphan*/  EVP_SealFinal (unsigned char*,unsigned char*,int*) ; 
 int /*<<< orphan*/  EVP_SealInit (unsigned char*,int /*<<< orphan*/  const*,unsigned char**,int*,unsigned char*,unsigned char**,int) ; 
 int /*<<< orphan*/  EVP_SealUpdate (unsigned char*,unsigned char*,int*,unsigned char const*,int) ; 
 int /*<<< orphan*/ * EVP_aes_256_cbc () ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_zalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char const*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  TEST_ptr (unsigned char*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 unsigned char* load_example_rsa_key () ; 

__attribute__((used)) static int test_EVP_Enveloped(void)
{
    int ret = 0;
    EVP_CIPHER_CTX *ctx = NULL;
    EVP_PKEY *keypair = NULL;
    unsigned char *kek = NULL;
    unsigned char iv[EVP_MAX_IV_LENGTH];
    static const unsigned char msg[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    int len, kek_len, ciphertext_len, plaintext_len;
    unsigned char ciphertext[32], plaintext[16];
    const EVP_CIPHER *type = EVP_aes_256_cbc();

    if (!TEST_ptr(keypair = load_example_rsa_key())
            || !TEST_ptr(kek = OPENSSL_zalloc(EVP_PKEY_size(keypair)))
            || !TEST_ptr(ctx = EVP_CIPHER_CTX_new())
            || !TEST_true(EVP_SealInit(ctx, type, &kek, &kek_len, iv,
                                       &keypair, 1))
            || !TEST_true(EVP_SealUpdate(ctx, ciphertext, &ciphertext_len,
                                         msg, sizeof(msg)))
            || !TEST_true(EVP_SealFinal(ctx, ciphertext + ciphertext_len,
                                        &len)))
        goto err;

    ciphertext_len += len;

    if (!TEST_true(EVP_OpenInit(ctx, type, kek, kek_len, iv, keypair))
            || !TEST_true(EVP_OpenUpdate(ctx, plaintext, &plaintext_len,
                                         ciphertext, ciphertext_len))
            || !TEST_true(EVP_OpenFinal(ctx, plaintext + plaintext_len, &len)))
        goto err;

    plaintext_len += len;
    if (!TEST_mem_eq(msg, sizeof(msg), plaintext, plaintext_len))
        goto err;

    ret = 1;
err:
    OPENSSL_free(kek);
    EVP_PKEY_free(keypair);
    EVP_CIPHER_CTX_free(ctx);
    return ret;
}