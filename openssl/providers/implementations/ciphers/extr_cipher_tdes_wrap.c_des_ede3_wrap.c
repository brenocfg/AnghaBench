#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned char* iv; TYPE_1__* hw; int /*<<< orphan*/  libctx; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* cipher ) (TYPE_2__*,unsigned char*,unsigned char*,size_t) ;} ;
typedef  TYPE_2__ PROV_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_reverse (unsigned char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int /*<<< orphan*/  SHA1 (unsigned char const*,size_t,unsigned char*) ; 
 int SHA_DIGEST_LENGTH ; 
 size_t TDES_IVLEN ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char const*,size_t) ; 
 scalar_t__ rand_bytes_ex (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,unsigned char*,unsigned char*,size_t) ; 
 unsigned char* wrap_iv ; 

__attribute__((used)) static int des_ede3_wrap(PROV_CIPHER_CTX *ctx, unsigned char *out,
                         const unsigned char *in, size_t inl)
{
    unsigned char sha1tmp[SHA_DIGEST_LENGTH];
    size_t ivlen = TDES_IVLEN;
    size_t icvlen = TDES_IVLEN;
    size_t len = inl + ivlen + icvlen;

    if (out == NULL)
        return len;

    /* Copy input to output buffer + 8 so we have space for IV */
    memmove(out + ivlen, in, inl);
    /* Work out ICV */
    SHA1(in, inl, sha1tmp);
    memcpy(out + inl + ivlen, sha1tmp, icvlen);
    OPENSSL_cleanse(sha1tmp, SHA_DIGEST_LENGTH);
    /* Generate random IV */
    if (rand_bytes_ex(ctx->libctx, ctx->iv, ivlen) <= 0)
        return 0;
    memcpy(out, ctx->iv, ivlen);
    /* Encrypt everything after IV in place */
    ctx->hw->cipher(ctx, out + ivlen, out + ivlen, inl + ivlen);
    BUF_reverse(out, NULL, len);
    memcpy(ctx->iv, wrap_iv, ivlen);
    ctx->hw->cipher(ctx, out, out, len);
    return len;
}