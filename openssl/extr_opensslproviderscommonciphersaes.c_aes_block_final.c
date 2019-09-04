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
struct TYPE_6__ {unsigned char* buf; size_t bufsz; scalar_t__ pad; TYPE_1__* ciph; scalar_t__ enc; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* cipher ) (TYPE_2__*,unsigned char*,unsigned char*,size_t) ;} ;
typedef  TYPE_2__ PROV_AES_KEY ;

/* Variables and functions */
 size_t AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  PROV_F_AES_BLOCK_FINAL ; 
 int /*<<< orphan*/  PROV_R_CIPHER_OPERATION_FAILED ; 
 int /*<<< orphan*/  PROV_R_OUTPUT_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  PROV_R_WRONG_FINAL_BLOCK_LENGTH ; 
 int /*<<< orphan*/  PROVerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  padblock (unsigned char*,size_t*,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  unpadblock (unsigned char*,size_t*,size_t) ; 

__attribute__((used)) static int aes_block_final(void *vctx, unsigned char *out, size_t *outl,
                           size_t outsize)
{
    PROV_AES_KEY *ctx = (PROV_AES_KEY *)vctx;

    if (ctx->enc) {
        if (ctx->pad) {
            padblock(ctx->buf, &ctx->bufsz, AES_BLOCK_SIZE);
        } else if (ctx->bufsz == 0) {
            *outl = 0;
            return 1;
        } else if (ctx->bufsz != AES_BLOCK_SIZE) {
            PROVerr(PROV_F_AES_BLOCK_FINAL, PROV_R_WRONG_FINAL_BLOCK_LENGTH);
            return 0;
        }

        if (outsize < AES_BLOCK_SIZE) {
            PROVerr(PROV_F_AES_BLOCK_FINAL, PROV_R_OUTPUT_BUFFER_TOO_SMALL);
            return 0;
        }
        if (!ctx->ciph->cipher(ctx, out, ctx->buf, AES_BLOCK_SIZE)) {
            PROVerr(PROV_F_AES_BLOCK_FINAL, PROV_R_CIPHER_OPERATION_FAILED);
            return 0;
        }
        ctx->bufsz = 0;
        *outl = AES_BLOCK_SIZE;
        return 1;
    }

    /* Decrypting */
    if (ctx->bufsz != AES_BLOCK_SIZE) {
        if (ctx->bufsz == 0 && !ctx->pad) {
            *outl = 0;
            return 1;
        }
        PROVerr(PROV_F_AES_BLOCK_FINAL, PROV_R_WRONG_FINAL_BLOCK_LENGTH);
        return 0;
    }

    if (!ctx->ciph->cipher(ctx, ctx->buf, ctx->buf, AES_BLOCK_SIZE)) {
        PROVerr(PROV_F_AES_BLOCK_FINAL, PROV_R_CIPHER_OPERATION_FAILED);
        return 0;
    }

    if (ctx->pad && !unpadblock(ctx->buf, &ctx->bufsz, AES_BLOCK_SIZE)) {
        /* PROVerr already called */
        return 0;
    }

    if (outsize < ctx->bufsz) {
        PROVerr(PROV_F_AES_BLOCK_FINAL, PROV_R_OUTPUT_BUFFER_TOO_SMALL);
        return 0;
    }
    memcpy(out, ctx->buf, ctx->bufsz);
    *outl = ctx->bufsz;
    ctx->bufsz = 0;
    return 1;
}