#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  (* block128_f ) (int*,int*,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  alen ;
struct TYPE_6__ {int* c; } ;
struct TYPE_5__ {int* c; } ;
struct TYPE_7__ {int /*<<< orphan*/  blocks; int /*<<< orphan*/  key; TYPE_2__ cmac; TYPE_1__ nonce; int /*<<< orphan*/  (* block ) (int*,int*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ CCM128_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int*,int*,int /*<<< orphan*/ ) ; 

void CRYPTO_ccm128_aad(CCM128_CONTEXT *ctx,
                       const unsigned char *aad, size_t alen)
{
    unsigned int i;
    block128_f block = ctx->block;

    if (alen == 0)
        return;

    ctx->nonce.c[0] |= 0x40;    /* set Adata flag */
    (*block) (ctx->nonce.c, ctx->cmac.c, ctx->key), ctx->blocks++;

    if (alen < (0x10000 - 0x100)) {
        ctx->cmac.c[0] ^= (u8)(alen >> 8);
        ctx->cmac.c[1] ^= (u8)alen;
        i = 2;
    } else if (sizeof(alen) == 8
               && alen >= (size_t)1 << (32 % (sizeof(alen) * 8))) {
        ctx->cmac.c[0] ^= 0xFF;
        ctx->cmac.c[1] ^= 0xFF;
        ctx->cmac.c[2] ^= (u8)(alen >> (56 % (sizeof(alen) * 8)));
        ctx->cmac.c[3] ^= (u8)(alen >> (48 % (sizeof(alen) * 8)));
        ctx->cmac.c[4] ^= (u8)(alen >> (40 % (sizeof(alen) * 8)));
        ctx->cmac.c[5] ^= (u8)(alen >> (32 % (sizeof(alen) * 8)));
        ctx->cmac.c[6] ^= (u8)(alen >> 24);
        ctx->cmac.c[7] ^= (u8)(alen >> 16);
        ctx->cmac.c[8] ^= (u8)(alen >> 8);
        ctx->cmac.c[9] ^= (u8)alen;
        i = 10;
    } else {
        ctx->cmac.c[0] ^= 0xFF;
        ctx->cmac.c[1] ^= 0xFE;
        ctx->cmac.c[2] ^= (u8)(alen >> 24);
        ctx->cmac.c[3] ^= (u8)(alen >> 16);
        ctx->cmac.c[4] ^= (u8)(alen >> 8);
        ctx->cmac.c[5] ^= (u8)alen;
        i = 6;
    }

    do {
        for (; i < 16 && alen; ++i, ++aad, --alen)
            ctx->cmac.c[i] ^= *aad;
        (*block) (ctx->cmac.c, ctx->cmac.c, ctx->key), ctx->blocks++;
        i = 0;
    } while (alen);
}