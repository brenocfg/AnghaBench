#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int /*<<< orphan*/  mlen ;
struct TYPE_4__ {int* c; scalar_t__* u; } ;
struct TYPE_5__ {TYPE_1__ nonce; } ;
typedef  TYPE_2__ CCM128_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,unsigned char const*,int) ; 

int CRYPTO_ccm128_setiv(CCM128_CONTEXT *ctx,
                        const unsigned char *nonce, size_t nlen, size_t mlen)
{
    unsigned int L = ctx->nonce.c[0] & 7; /* the L parameter */

    if (nlen < (14 - L))
        return -1;              /* nonce is too short */

    if (sizeof(mlen) == 8 && L >= 3) {
        ctx->nonce.c[8] = (u8)(mlen >> (56 % (sizeof(mlen) * 8)));
        ctx->nonce.c[9] = (u8)(mlen >> (48 % (sizeof(mlen) * 8)));
        ctx->nonce.c[10] = (u8)(mlen >> (40 % (sizeof(mlen) * 8)));
        ctx->nonce.c[11] = (u8)(mlen >> (32 % (sizeof(mlen) * 8)));
    } else
        ctx->nonce.u[1] = 0;

    ctx->nonce.c[12] = (u8)(mlen >> 24);
    ctx->nonce.c[13] = (u8)(mlen >> 16);
    ctx->nonce.c[14] = (u8)(mlen >> 8);
    ctx->nonce.c[15] = (u8)mlen;

    ctx->nonce.c[0] &= ~0x40;   /* clear Adata flag */
    memcpy(&ctx->nonce.c[1], nonce, 14 - L);

    return 0;
}