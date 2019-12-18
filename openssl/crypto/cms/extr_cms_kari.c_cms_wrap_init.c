#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ctx; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  TYPE_1__ CMS_KeyAgreeRecipientInfo ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_CIPHER_CTX_cipher (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_CIPHER_CTX_mode (int /*<<< orphan*/ *) ; 
 int EVP_CIPHER_key_length (int /*<<< orphan*/  const*) ; 
 scalar_t__ EVP_CIPHER_type (int /*<<< orphan*/  const*) ; 
 scalar_t__ EVP_CIPH_WRAP_MODE ; 
 int EVP_EncryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_aes_128_wrap () ; 
 int /*<<< orphan*/ * EVP_aes_192_wrap () ; 
 int /*<<< orphan*/ * EVP_aes_256_wrap () ; 
 int /*<<< orphan*/ * EVP_des_ede3_wrap () ; 
 scalar_t__ NID_des_ede3_cbc ; 

__attribute__((used)) static int cms_wrap_init(CMS_KeyAgreeRecipientInfo *kari,
                         const EVP_CIPHER *cipher)
{
    EVP_CIPHER_CTX *ctx = kari->ctx;
    const EVP_CIPHER *kekcipher;
    int keylen = EVP_CIPHER_key_length(cipher);
    /* If a suitable wrap algorithm is already set nothing to do */
    kekcipher = EVP_CIPHER_CTX_cipher(ctx);

    if (kekcipher) {
        if (EVP_CIPHER_CTX_mode(ctx) != EVP_CIPH_WRAP_MODE)
            return 0;
        return 1;
    }
    /*
     * Pick a cipher based on content encryption cipher. If it is DES3 use
     * DES3 wrap otherwise use AES wrap similar to key size.
     */
#ifndef OPENSSL_NO_DES
    if (EVP_CIPHER_type(cipher) == NID_des_ede3_cbc)
        kekcipher = EVP_des_ede3_wrap();
    else
#endif
    if (keylen <= 16)
        kekcipher = EVP_aes_128_wrap();
    else if (keylen <= 24)
        kekcipher = EVP_aes_192_wrap();
    else
        kekcipher = EVP_aes_256_wrap();
    return EVP_EncryptInit_ex(ctx, kekcipher, NULL, NULL, NULL);
}