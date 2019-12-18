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
struct TYPE_9__ {int /*<<< orphan*/  byte; } ;
struct TYPE_11__ {scalar_t__ crypto_ok; scalar_t__ final_ret; int /*<<< orphan*/  cipher_ctx; TYPE_1__ tag; } ;
struct TYPE_10__ {int* byte; } ;
typedef  TYPE_2__ SIV_BLOCK ;
typedef  TYPE_3__ SIV128_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  SIV_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siv128_do_encrypt (int /*<<< orphan*/ ,unsigned char*,unsigned char const*,size_t,TYPE_2__*) ; 
 int /*<<< orphan*/  siv128_do_s2v_p (TYPE_3__*,TYPE_2__*,unsigned char const*,size_t) ; 

int CRYPTO_siv128_encrypt(SIV128_CONTEXT *ctx,
                          const unsigned char *in, unsigned char *out,
                          size_t len)
{
    SIV_BLOCK q;

    /* can only do one crypto operation */
    if (ctx->crypto_ok == 0)
        return 0;
    ctx->crypto_ok--;

    if (!siv128_do_s2v_p(ctx, &q, in, len))
        return 0;

    memcpy(ctx->tag.byte, &q, SIV_LEN);
    q.byte[8] &= 0x7f;
    q.byte[12] &= 0x7f;

    if (!siv128_do_encrypt(ctx->cipher_ctx, out, in, len, &q))
        return 0;
    ctx->final_ret = 0;
    return len;
}