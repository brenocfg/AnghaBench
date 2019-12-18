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
struct TYPE_3__ {size_t block_size; size_t bufsz; scalar_t__ md_size; int* buf; int pad; int /*<<< orphan*/  A; } ;
typedef  TYPE_1__ KECCAK1600_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA3_absorb (int /*<<< orphan*/ ,int*,size_t,size_t) ; 
 int /*<<< orphan*/  SHA3_squeeze (int /*<<< orphan*/ ,unsigned char*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,size_t) ; 

int sha3_final(unsigned char *md, KECCAK1600_CTX *ctx)
{
    size_t bsz = ctx->block_size;
    size_t num = ctx->bufsz;

    if (ctx->md_size == 0)
        return 1;

    /*
     * Pad the data with 10*1. Note that |num| can be |bsz - 1|
     * in which case both byte operations below are performed on
     * same byte...
     */
    memset(ctx->buf + num, 0, bsz - num);
    ctx->buf[num] = ctx->pad;
    ctx->buf[bsz - 1] |= 0x80;

    (void)SHA3_absorb(ctx->A, ctx->buf, bsz, bsz);

    SHA3_squeeze(ctx->A, md, ctx->md_size, bsz);

    return 1;
}