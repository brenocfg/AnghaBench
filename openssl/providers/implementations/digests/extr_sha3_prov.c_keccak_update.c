#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t (* absorb ) (TYPE_2__*,unsigned char const*,size_t const) ;} ;
struct TYPE_6__ {size_t block_size; size_t bufsz; unsigned char const* buf; TYPE_1__ meth; } ;
typedef  TYPE_2__ KECCAK1600_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char const*,unsigned char const*,size_t) ; 
 size_t stub1 (TYPE_2__*,unsigned char const*,size_t const) ; 
 size_t stub2 (TYPE_2__*,unsigned char const*,size_t) ; 

__attribute__((used)) static int keccak_update(void *vctx, const unsigned char *inp, size_t len)
{
    KECCAK1600_CTX *ctx = vctx;
    const size_t bsz = ctx->block_size;
    size_t num, rem;

    if (len == 0)
        return 1;

    /* Is there anything in the buffer already ? */
    if ((num = ctx->bufsz) != 0) {
        /* Calculate how much space is left in the buffer */
        rem = bsz - num;
        /* If the new input does not fill the buffer then just add it */
        if (len < rem) {
            memcpy(ctx->buf + num, inp, len);
            ctx->bufsz += len;
            return 1;
        }
        /* otherwise fill up the buffer and absorb the buffer */
        memcpy(ctx->buf + num, inp, rem);
        /* Update the input pointer */
        inp += rem;
        len -= rem;
        ctx->meth.absorb(ctx, ctx->buf, bsz);
        ctx->bufsz = 0;
    }
    /* Absorb the input - rem = leftover part of the input < blocksize) */
    rem = ctx->meth.absorb(ctx, inp, len);
    /* Copy the leftover bit of the input into the buffer */
    if (rem) {
        memcpy(ctx->buf, inp + len - rem, rem);
        ctx->bufsz = rem;
    }
    return 1;
}