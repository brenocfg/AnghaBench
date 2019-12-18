#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned char* byte; } ;
struct TYPE_11__ {scalar_t__ crypto_ok; scalar_t__ final_ret; TYPE_1__ tag; int /*<<< orphan*/  cipher_ctx; } ;
struct TYPE_10__ {int* byte; int* word; } ;
typedef  TYPE_2__ SIV_BLOCK ;
typedef  TYPE_3__ SIV128_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,size_t) ; 
 int SIV_LEN ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,unsigned char*,int) ; 
 int /*<<< orphan*/  siv128_do_encrypt (int /*<<< orphan*/ ,unsigned char*,unsigned char const*,size_t,TYPE_2__*) ; 
 int /*<<< orphan*/  siv128_do_s2v_p (TYPE_3__*,TYPE_2__*,unsigned char*,size_t) ; 

int CRYPTO_siv128_decrypt(SIV128_CONTEXT *ctx,
                          const unsigned char *in, unsigned char *out,
                          size_t len)
{
    unsigned char* p;
    SIV_BLOCK t, q;
    int i;

    /* can only do one crypto operation */
    if (ctx->crypto_ok == 0)
        return 0;
    ctx->crypto_ok--;

    memcpy(&q, ctx->tag.byte, SIV_LEN);
    q.byte[8] &= 0x7f;
    q.byte[12] &= 0x7f;

    if (!siv128_do_encrypt(ctx->cipher_ctx, out, in, len, &q)
        || !siv128_do_s2v_p(ctx, &t, out, len))
        return 0;

    p = ctx->tag.byte;
    for (i = 0; i < SIV_LEN; i++)
        t.byte[i] ^= p[i];

    if ((t.word[0] | t.word[1]) != 0) {
        OPENSSL_cleanse(out, len);
        return 0;
    }
    ctx->final_ret = 0;
    return len;
}