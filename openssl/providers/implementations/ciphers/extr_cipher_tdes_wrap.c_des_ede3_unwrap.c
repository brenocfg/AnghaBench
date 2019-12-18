#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned char* iv; TYPE_1__* hw; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* cipher ) (TYPE_2__*,unsigned char*,unsigned char*,int) ;} ;
typedef  TYPE_2__ PROV_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_reverse (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  CRYPTO_memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,size_t) ; 
 int /*<<< orphan*/  SHA1 (unsigned char*,size_t,unsigned char*) ; 
 int SHA_DIGEST_LENGTH ; 
 int TDES_IVLEN ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__*,unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  wrap_iv ; 

__attribute__((used)) static int des_ede3_unwrap(PROV_CIPHER_CTX *ctx, unsigned char *out,
                           const unsigned char *in, size_t inl)
{
    unsigned char icv[8], iv[TDES_IVLEN], sha1tmp[SHA_DIGEST_LENGTH];
    int rv = -1;

    if (inl < 24)
        return -1;
    if (out == NULL)
        return inl - 16;

    memcpy(ctx->iv, wrap_iv, 8);
    /* Decrypt first block which will end up as icv */
    ctx->hw->cipher(ctx, icv, in, 8);
    /* Decrypt central blocks */
    /*
     * If decrypting in place move whole output along a block so the next
     * des_ede_cbc_cipher is in place.
     */
    if (out == in) {
        memmove(out, out + 8, inl - 8);
        in -= 8;
    }
    ctx->hw->cipher(ctx, out, in + 8, inl - 16);
    /* Decrypt final block which will be IV */
    ctx->hw->cipher(ctx, iv, in + inl - 8, 8);
    /* Reverse order of everything */
    BUF_reverse(icv, NULL, 8);
    BUF_reverse(out, NULL, inl - 16);
    BUF_reverse(ctx->iv, iv, 8);
    /* Decrypt again using new IV */
    ctx->hw->cipher(ctx, out, out, inl - 16);
    ctx->hw->cipher(ctx, icv, icv, 8);
    /* Work out SHA1 hash of first portion */
    SHA1(out, inl - 16, sha1tmp);

    if (!CRYPTO_memcmp(sha1tmp, icv, 8))
        rv = inl - 16;
    OPENSSL_cleanse(icv, 8);
    OPENSSL_cleanse(sha1tmp, SHA_DIGEST_LENGTH);
    OPENSSL_cleanse(iv, 8);
    OPENSSL_cleanse(ctx->iv, sizeof(ctx->iv));
    if (rv == -1)
        OPENSSL_cleanse(out, inl - 16);

    return rv;
}