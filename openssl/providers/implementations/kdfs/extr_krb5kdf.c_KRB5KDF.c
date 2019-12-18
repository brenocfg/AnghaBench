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
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t EVP_CIPHER_CTX_block_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int EVP_CIPHER_CTX_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_CIPHER_nid (int /*<<< orphan*/  const*) ; 
 int EVP_EncryptFinal_ex (int /*<<< orphan*/ *,unsigned char*,int*) ; 
 int EVP_EncryptUpdate (int /*<<< orphan*/ *,unsigned char*,int*,unsigned char*,size_t) ; 
 int EVP_MAX_BLOCK_LENGTH ; 
 scalar_t__ NID_des_ede3_cbc ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int /*<<< orphan*/  PROV_R_FAILED_TO_GENERATE_KEY ; 
 int /*<<< orphan*/  PROV_R_INVALID_CONSTANT_LENGTH ; 
 int /*<<< orphan*/  PROV_R_WRONG_FINAL_BLOCK_LENGTH ; 
 int /*<<< orphan*/  PROV_R_WRONG_OUTPUT_BUFFER_SIZE ; 
 int cipher_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int fixup_des3_key (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  n_fold (unsigned char*,size_t,unsigned char const*,size_t) ; 

__attribute__((used)) static int KRB5KDF(const EVP_CIPHER *cipher, ENGINE *engine,
                   const unsigned char *key, size_t key_len,
                   const unsigned char *constant, size_t constant_len,
                   unsigned char *okey, size_t okey_len)
{
    EVP_CIPHER_CTX *ctx = NULL;
    unsigned char block[EVP_MAX_BLOCK_LENGTH * 2];
    unsigned char *plainblock, *cipherblock;
    size_t blocksize;
    size_t cipherlen;
    size_t osize;
    int des3_no_fixup = 0;
    int ret;

    if (key_len != okey_len) {
        /* special case for 3des, where the caller may be requesting
         * the random raw key, instead of the fixed up key  */
        if (EVP_CIPHER_nid(cipher) == NID_des_ede3_cbc &&
            key_len == 24 && okey_len == 21) {
                des3_no_fixup = 1;
        } else {
            ERR_raise(ERR_LIB_PROV, PROV_R_WRONG_OUTPUT_BUFFER_SIZE);
            return 0;
        }
    }

    ctx = EVP_CIPHER_CTX_new();
    if (ctx == NULL)
        return 0;

    ret = cipher_init(ctx, cipher, engine, key, key_len);
    if (!ret)
        goto out;

    /* Initialize input block */
    blocksize = EVP_CIPHER_CTX_block_size(ctx);

    if (constant_len > blocksize) {
        ERR_raise(ERR_LIB_PROV, PROV_R_INVALID_CONSTANT_LENGTH);
        ret = 0;
        goto out;
    }

    n_fold(block, blocksize, constant, constant_len);
    plainblock = block;
    cipherblock = block + EVP_MAX_BLOCK_LENGTH;

    for (osize = 0; osize < okey_len; osize += cipherlen) {
        int olen;

        ret = EVP_EncryptUpdate(ctx, cipherblock, &olen,
                                plainblock, blocksize);
        if (!ret)
            goto out;
        cipherlen = olen;
        ret = EVP_EncryptFinal_ex(ctx, cipherblock, &olen);
        if (!ret)
            goto out;
        if (olen != 0) {
            ERR_raise(ERR_LIB_PROV, PROV_R_WRONG_FINAL_BLOCK_LENGTH);
            ret = 0;
            goto out;
        }

        /* write cipherblock out */
        if (cipherlen > okey_len - osize)
            cipherlen = okey_len - osize;
        memcpy(okey + osize, cipherblock, cipherlen);

        if (okey_len > osize + cipherlen) {
            /* we need to reinitialize cipher context per spec */
            ret = EVP_CIPHER_CTX_reset(ctx);
            if (!ret)
                goto out;
            ret = cipher_init(ctx, cipher, engine, key, key_len);
            if (!ret)
                goto out;

            /* also swap block offsets so last ciphertext becomes new
             * plaintext */
            plainblock = cipherblock;
            if (cipherblock == block) {
                cipherblock += EVP_MAX_BLOCK_LENGTH;
            } else {
                cipherblock = block;
            }
        }
    }

#ifndef OPENSSL_NO_DES
    if (EVP_CIPHER_nid(cipher) == NID_des_ede3_cbc && !des3_no_fixup) {
        ret = fixup_des3_key(okey);
        if (!ret) {
            ERR_raise(ERR_LIB_PROV, PROV_R_FAILED_TO_GENERATE_KEY);
            goto out;
        }
    }
#endif

    ret = 1;

out:
    EVP_CIPHER_CTX_free(ctx);
    OPENSSL_cleanse(block, EVP_MAX_BLOCK_LENGTH * 2);
    return ret;
}