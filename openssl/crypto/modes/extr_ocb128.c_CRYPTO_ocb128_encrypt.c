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
typedef  size_t u64 ;
struct TYPE_11__ {int* c; } ;
struct TYPE_10__ {size_t blocks_processed; TYPE_2__ checksum; TYPE_2__ offset; } ;
struct TYPE_12__ {TYPE_1__ sess; int /*<<< orphan*/  keyenc; int /*<<< orphan*/  (* encrypt ) (unsigned char*,unsigned char const*,int /*<<< orphan*/ ) ;TYPE_2__ l_star; scalar_t__ l; int /*<<< orphan*/  (* stream ) (unsigned char const*,unsigned char*,size_t,int /*<<< orphan*/ ,size_t,int*,unsigned char const**,int*) ;} ;
typedef  TYPE_2__ OCB_BLOCK ;
typedef  TYPE_3__ OCB128_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocb_block16_xor (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ocb_block_xor (unsigned char const*,unsigned char const*,size_t,unsigned char*) ; 
 TYPE_2__* ocb_lookup_l (TYPE_3__*,size_t) ; 
 size_t ocb_ntz (size_t) ; 
 int /*<<< orphan*/  stub1 (unsigned char const*,unsigned char*,size_t,int /*<<< orphan*/ ,size_t,int*,unsigned char const**,int*) ; 
 int /*<<< orphan*/  stub2 (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (unsigned char*,unsigned char const*,int /*<<< orphan*/ ) ; 

int CRYPTO_ocb128_encrypt(OCB128_CONTEXT *ctx,
                          const unsigned char *in, unsigned char *out,
                          size_t len)
{
    u64 i, all_num_blocks;
    size_t num_blocks, last_len;

    /*
     * Calculate the number of blocks of data to be encrypted provided now, and
     * so far
     */
    num_blocks = len / 16;
    all_num_blocks = num_blocks + ctx->sess.blocks_processed;

    if (num_blocks && all_num_blocks == (size_t)all_num_blocks
        && ctx->stream != NULL) {
        size_t max_idx = 0, top = (size_t)all_num_blocks;

        /*
         * See how many L_{i} entries we need to process data at hand
         * and pre-compute missing entries in the table [if any]...
         */
        while (top >>= 1)
            max_idx++;
        if (ocb_lookup_l(ctx, max_idx) == NULL)
            return 0;

        ctx->stream(in, out, num_blocks, ctx->keyenc,
                    (size_t)ctx->sess.blocks_processed + 1, ctx->sess.offset.c,
                    (const unsigned char (*)[16])ctx->l, ctx->sess.checksum.c);
    } else {
        /* Loop through all full blocks to be encrypted */
        for (i = ctx->sess.blocks_processed + 1; i <= all_num_blocks; i++) {
            OCB_BLOCK *lookup;
            OCB_BLOCK tmp;

            /* Offset_i = Offset_{i-1} xor L_{ntz(i)} */
            lookup = ocb_lookup_l(ctx, ocb_ntz(i));
            if (lookup == NULL)
                return 0;
            ocb_block16_xor(&ctx->sess.offset, lookup, &ctx->sess.offset);

            memcpy(tmp.c, in, 16);
            in += 16;

            /* Checksum_i = Checksum_{i-1} xor P_i */
            ocb_block16_xor(&tmp, &ctx->sess.checksum, &ctx->sess.checksum);

            /* C_i = Offset_i xor ENCIPHER(K, P_i xor Offset_i) */
            ocb_block16_xor(&ctx->sess.offset, &tmp, &tmp);
            ctx->encrypt(tmp.c, tmp.c, ctx->keyenc);
            ocb_block16_xor(&ctx->sess.offset, &tmp, &tmp);

            memcpy(out, tmp.c, 16);
            out += 16;
        }
    }

    /*
     * Check if we have any partial blocks left over. This is only valid in the
     * last call to this function
     */
    last_len = len % 16;

    if (last_len > 0) {
        OCB_BLOCK pad;

        /* Offset_* = Offset_m xor L_* */
        ocb_block16_xor(&ctx->sess.offset, &ctx->l_star, &ctx->sess.offset);

        /* Pad = ENCIPHER(K, Offset_*) */
        ctx->encrypt(ctx->sess.offset.c, pad.c, ctx->keyenc);

        /* C_* = P_* xor Pad[1..bitlen(P_*)] */
        ocb_block_xor(in, pad.c, last_len, out);

        /* Checksum_* = Checksum_m xor (P_* || 1 || zeros(127-bitlen(P_*))) */
        memset(pad.c, 0, 16);           /* borrow pad */
        memcpy(pad.c, in, last_len);
        pad.c[last_len] = 0x80;
        ocb_block16_xor(&pad, &ctx->sess.checksum, &ctx->sess.checksum);
    }

    ctx->sess.blocks_processed = all_num_blocks;

    return 1;
}