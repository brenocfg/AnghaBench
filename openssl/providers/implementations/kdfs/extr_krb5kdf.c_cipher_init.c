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
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int EVP_CIPHER_CTX_key_length (int /*<<< orphan*/ *) ; 
 int EVP_CIPHER_CTX_set_key_length (int /*<<< orphan*/ *,size_t) ; 
 int EVP_CIPHER_CTX_set_padding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int EVP_EncryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cipher_init(EVP_CIPHER_CTX *ctx,
                       const EVP_CIPHER *cipher, ENGINE *engine,
                       const unsigned char *key, size_t key_len)
{
    int klen, ret;

    ret = EVP_EncryptInit_ex(ctx, cipher, engine, key, NULL);
    if (!ret)
        goto out;
    /* set the key len for the odd variable key len cipher */
    klen = EVP_CIPHER_CTX_key_length(ctx);
    if (key_len != (size_t)klen) {
        ret = EVP_CIPHER_CTX_set_key_length(ctx, key_len);
        if (!ret)
            goto out;
    }
    /* we never want padding, either the length requested is a multiple of
     * the cipher block size or we are passed a cipher that can cope with
     * partial blocks via techniques like cipher text stealing */
    ret = EVP_CIPHER_CTX_set_padding(ctx, 0);
    if (!ret)
        goto out;

out:
    return ret;
}