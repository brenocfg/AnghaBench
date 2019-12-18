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
typedef  int u8 ;
typedef  int /*<<< orphan*/  block128_f ;
struct TYPE_4__ {int* c; } ;
struct TYPE_5__ {void* key; int /*<<< orphan*/  block; scalar_t__ blocks; TYPE_1__ nonce; } ;
typedef  TYPE_2__ CCM128_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

void CRYPTO_ccm128_init(CCM128_CONTEXT *ctx,
                        unsigned int M, unsigned int L, void *key,
                        block128_f block)
{
    memset(ctx->nonce.c, 0, sizeof(ctx->nonce.c));
    ctx->nonce.c[0] = ((u8)(L - 1) & 7) | (u8)(((M - 2) / 2) & 7) << 3;
    ctx->blocks = 0;
    ctx->block = block;
    ctx->key = key;
}