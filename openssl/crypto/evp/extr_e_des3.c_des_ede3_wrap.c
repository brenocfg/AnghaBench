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

/* Variables and functions */
 int /*<<< orphan*/  BUF_reverse (unsigned char*,int /*<<< orphan*/ *,size_t) ; 
 unsigned char* EVP_CIPHER_CTX_iv_noconst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 scalar_t__ RAND_bytes (unsigned char*,int) ; 
 int /*<<< orphan*/  SHA1 (unsigned char const*,size_t,unsigned char*) ; 
 int SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  des_ede_cbc_cipher (int /*<<< orphan*/ *,unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char const*,size_t) ; 
 unsigned char* wrap_iv ; 

__attribute__((used)) static int des_ede3_wrap(EVP_CIPHER_CTX *ctx, unsigned char *out,
                         const unsigned char *in, size_t inl)
{
    unsigned char sha1tmp[SHA_DIGEST_LENGTH];
    if (out == NULL)
        return inl + 16;
    /* Copy input to output buffer + 8 so we have space for IV */
    memmove(out + 8, in, inl);
    /* Work out ICV */
    SHA1(in, inl, sha1tmp);
    memcpy(out + inl + 8, sha1tmp, 8);
    OPENSSL_cleanse(sha1tmp, SHA_DIGEST_LENGTH);
    /* Generate random IV */
    if (RAND_bytes(EVP_CIPHER_CTX_iv_noconst(ctx), 8) <= 0)
        return -1;
    memcpy(out, EVP_CIPHER_CTX_iv_noconst(ctx), 8);
    /* Encrypt everything after IV in place */
    des_ede_cbc_cipher(ctx, out + 8, out + 8, inl + 8);
    BUF_reverse(out, NULL, inl + 16);
    memcpy(EVP_CIPHER_CTX_iv_noconst(ctx), wrap_iv, 8);
    des_ede_cbc_cipher(ctx, out, out, inl + 16);
    return inl + 16;
}