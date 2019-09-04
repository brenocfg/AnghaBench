#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ num; int /*<<< orphan*/  opaque; void** nonce; } ;
typedef  TYPE_1__ POLY1305 ;

/* Variables and functions */
 void* U8TOU32 (unsigned char const*) ; 
 int /*<<< orphan*/  poly1305_init (int /*<<< orphan*/ ,unsigned char const*) ; 

void Poly1305_Init(POLY1305 *ctx, const unsigned char key[32])
{
    ctx->nonce[0] = U8TOU32(&key[16]);
    ctx->nonce[1] = U8TOU32(&key[20]);
    ctx->nonce[2] = U8TOU32(&key[24]);
    ctx->nonce[3] = U8TOU32(&key[28]);

#ifndef POLY1305_ASM
    poly1305_init(ctx->opaque, key);
#else
    /*
     * Unlike reference poly1305_init assembly counterpart is expected
     * to return a value: non-zero if it initializes ctx->func, and zero
     * otherwise. Latter is to simplify assembly in cases when there no
     * multiple code paths to switch between.
     */
    if (!poly1305_init(ctx->opaque, key, &ctx->func)) {
        ctx->func.blocks = poly1305_blocks;
        ctx->func.emit = poly1305_emit;
    }
#endif

    ctx->num = 0;

}