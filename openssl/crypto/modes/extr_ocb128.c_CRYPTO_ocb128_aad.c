#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_11__ {int* c; } ;
struct TYPE_10__ {scalar_t__ blocks_hashed; TYPE_2__ sum; TYPE_2__ offset_aad; } ;
struct TYPE_12__ {TYPE_1__ sess; int /*<<< orphan*/  keyenc; int /*<<< orphan*/  (* encrypt ) (int*,int*,int /*<<< orphan*/ ) ;TYPE_2__ l_star; } ;
typedef  TYPE_2__ OCB_BLOCK ;
typedef  TYPE_3__ OCB128_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocb_block16_xor (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* ocb_lookup_l (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocb_ntz (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int*,int*,int /*<<< orphan*/ ) ; 

int CRYPTO_ocb128_aad(OCB128_CONTEXT *ctx, const unsigned char *aad,
                      size_t len)
{
    u64 i, all_num_blocks;
    size_t num_blocks, last_len;
    OCB_BLOCK tmp;

    /* Calculate the number of blocks of AAD provided now, and so far */
    num_blocks = len / 16;
    all_num_blocks = num_blocks + ctx->sess.blocks_hashed;

    /* Loop through all full blocks of AAD */
    for (i = ctx->sess.blocks_hashed + 1; i <= all_num_blocks; i++) {
        OCB_BLOCK *lookup;

        /* Offset_i = Offset_{i-1} xor L_{ntz(i)} */
        lookup = ocb_lookup_l(ctx, ocb_ntz(i));
        if (lookup == NULL)
            return 0;
        ocb_block16_xor(&ctx->sess.offset_aad, lookup, &ctx->sess.offset_aad);

        memcpy(tmp.c, aad, 16);
        aad += 16;

        /* Sum_i = Sum_{i-1} xor ENCIPHER(K, A_i xor Offset_i) */
        ocb_block16_xor(&ctx->sess.offset_aad, &tmp, &tmp);
        ctx->encrypt(tmp.c, tmp.c, ctx->keyenc);
        ocb_block16_xor(&tmp, &ctx->sess.sum, &ctx->sess.sum);
    }

    /*
     * Check if we have any partial blocks left over. This is only valid in the
     * last call to this function
     */
    last_len = len % 16;

    if (last_len > 0) {
        /* Offset_* = Offset_m xor L_* */
        ocb_block16_xor(&ctx->sess.offset_aad, &ctx->l_star,
                        &ctx->sess.offset_aad);

        /* CipherInput = (A_* || 1 || zeros(127-bitlen(A_*))) xor Offset_* */
        memset(tmp.c, 0, 16);
        memcpy(tmp.c, aad, last_len);
        tmp.c[last_len] = 0x80;
        ocb_block16_xor(&ctx->sess.offset_aad, &tmp, &tmp);

        /* Sum = Sum_m xor ENCIPHER(K, CipherInput) */
        ctx->encrypt(tmp.c, tmp.c, ctx->keyenc);
        ocb_block16_xor(&tmp, &ctx->sess.sum, &ctx->sess.sum);
    }

    ctx->sess.blocks_hashed = all_num_blocks;

    return 1;
}