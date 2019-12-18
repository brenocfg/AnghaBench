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
struct TYPE_6__ {size_t blocksize; unsigned char const* buf; size_t bufsz; TYPE_1__* hw; scalar_t__ pad; scalar_t__ enc; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* cipher ) (TYPE_2__*,unsigned char*,unsigned char const*,size_t) ;} ;
typedef  TYPE_2__ PROV_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_CIPHER_OPERATION_FAILED ; 
 int /*<<< orphan*/  PROV_R_OUTPUT_BUFFER_TOO_SMALL ; 
 size_t fillblock (unsigned char const*,size_t*,size_t,unsigned char const**,size_t*) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  trailingdata (unsigned char const*,size_t*,size_t,unsigned char const**,size_t*) ; 

int cipher_generic_block_update(void *vctx, unsigned char *out, size_t *outl,
                                size_t outsize, const unsigned char *in,
                                size_t inl)
{
    size_t outlint = 0;
    PROV_CIPHER_CTX *ctx = (PROV_CIPHER_CTX *)vctx;
    size_t blksz = ctx->blocksize;
    size_t nextblocks = fillblock(ctx->buf, &ctx->bufsz, blksz, &in, &inl);

    /*
     * If we're decrypting and we end an update on a block boundary we hold
     * the last block back in case this is the last update call and the last
     * block is padded.
     */
    if (ctx->bufsz == blksz && (ctx->enc || inl > 0 || !ctx->pad)) {
        if (outsize < blksz) {
            ERR_raise(ERR_LIB_PROV, PROV_R_OUTPUT_BUFFER_TOO_SMALL);
            return 0;
        }
        if (!ctx->hw->cipher(ctx, out, ctx->buf, blksz)) {
            ERR_raise(ERR_LIB_PROV, PROV_R_CIPHER_OPERATION_FAILED);
            return 0;
        }
        ctx->bufsz = 0;
        outlint = blksz;
        out += blksz;
    }
    if (nextblocks > 0) {
        if (!ctx->enc && ctx->pad && nextblocks == inl) {
            if (!ossl_assert(inl >= blksz)) {
                ERR_raise(ERR_LIB_PROV, PROV_R_OUTPUT_BUFFER_TOO_SMALL);
                return 0;
            }
            nextblocks -= blksz;
        }
        outlint += nextblocks;
        if (outsize < outlint) {
            ERR_raise(ERR_LIB_PROV, PROV_R_OUTPUT_BUFFER_TOO_SMALL);
            return 0;
        }
        if (!ctx->hw->cipher(ctx, out, in, nextblocks)) {
            ERR_raise(ERR_LIB_PROV, PROV_R_CIPHER_OPERATION_FAILED);
            return 0;
        }
        in += nextblocks;
        inl -= nextblocks;
    }
    if (!trailingdata(ctx->buf, &ctx->bufsz, blksz, &in, &inl)) {
        /* ERR_raise already called */
        return 0;
    }

    *outl = outlint;
    return inl == 0;
}