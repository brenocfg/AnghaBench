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
struct TYPE_6__ {unsigned char const* buf; size_t bufsz; TYPE_1__* ciph; scalar_t__ pad; scalar_t__ enc; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* cipher ) (TYPE_2__*,unsigned char*,unsigned char const*,size_t) ;} ;
typedef  TYPE_2__ PROV_AES_KEY ;

/* Variables and functions */
 size_t AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  PROV_F_AES_BLOCK_UPDATE ; 
 int /*<<< orphan*/  PROV_R_CIPHER_OPERATION_FAILED ; 
 int /*<<< orphan*/  PROV_R_OUTPUT_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  PROVerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t fillblock (unsigned char const*,size_t*,size_t,unsigned char const**,size_t*) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  trailingdata (unsigned char const*,size_t*,size_t,unsigned char const**,size_t*) ; 

__attribute__((used)) static int aes_block_update(void *vctx, unsigned char *out, size_t *outl,
                            size_t outsize, const unsigned char *in, size_t inl)
{
    PROV_AES_KEY *ctx = (PROV_AES_KEY *)vctx;
    size_t nextblocks = fillblock(ctx->buf, &ctx->bufsz, AES_BLOCK_SIZE, &in,
                                  &inl);
    size_t outlint = 0;

    /*
     * If we're decrypting and we end an update on a block boundary we hold
     * the last block back in case this is the last update call and the last
     * block is padded.
     */
    if (ctx->bufsz == AES_BLOCK_SIZE
            && (ctx->enc || inl > 0 || !ctx->pad)) {
        if (outsize < AES_BLOCK_SIZE) {
            PROVerr(PROV_F_AES_BLOCK_UPDATE, PROV_R_OUTPUT_BUFFER_TOO_SMALL);
            return 0;
        }
        if (!ctx->ciph->cipher(ctx, out, ctx->buf, AES_BLOCK_SIZE)) {
            PROVerr(PROV_F_AES_BLOCK_UPDATE, PROV_R_CIPHER_OPERATION_FAILED);
            return 0;
        }
        ctx->bufsz = 0;
        outlint = AES_BLOCK_SIZE;
        out += AES_BLOCK_SIZE;
    }
    if (nextblocks > 0) {
        if (!ctx->enc && ctx->pad && nextblocks == inl) {
            if (!ossl_assert(inl >= AES_BLOCK_SIZE)) {
                PROVerr(PROV_F_AES_BLOCK_UPDATE, PROV_R_OUTPUT_BUFFER_TOO_SMALL);
                return 0;
            }
            nextblocks -= AES_BLOCK_SIZE;
        }
        outlint += nextblocks;
        if (outsize < outlint) {
            PROVerr(PROV_F_AES_BLOCK_UPDATE, PROV_R_OUTPUT_BUFFER_TOO_SMALL);
            return 0;
        }
        if (!ctx->ciph->cipher(ctx, out, in, nextblocks)) {
            PROVerr(PROV_F_AES_BLOCK_UPDATE, PROV_R_CIPHER_OPERATION_FAILED);
            return 0;
        }
        in += nextblocks;
        inl -= nextblocks;
    }
    if (!trailingdata(ctx->buf, &ctx->bufsz, AES_BLOCK_SIZE, &in, &inl)) {
        /* PROVerr already called */
        return 0;
    }

    *outl = outlint;
    return inl == 0;
}