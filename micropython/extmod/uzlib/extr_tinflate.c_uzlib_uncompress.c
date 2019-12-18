#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ dest; scalar_t__ dest_limit; int btype; int bfinal; int /*<<< orphan*/  dtree; int /*<<< orphan*/  ltree; } ;
typedef  TYPE_1__ TINF_DATA ;

/* Variables and functions */
 int TINF_DATA_ERROR ; 
 int TINF_DONE ; 
 int TINF_OK ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  tinf_build_fixed_trees (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int tinf_decode_trees (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int tinf_getbit (TYPE_1__*) ; 
 int tinf_inflate_block_data (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int tinf_inflate_uncompressed_block (TYPE_1__*) ; 
 int tinf_read_bits (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

int uzlib_uncompress(TINF_DATA *d)
{
    do {
        int res;

        /* start a new block */
        if (d->btype == -1) {
next_blk:
            /* read final block flag */
            d->bfinal = tinf_getbit(d);
            /* read block type (2 bits) */
            d->btype = tinf_read_bits(d, 2, 0);

            #if UZLIB_CONF_DEBUG_LOG >= 1
            printf("Started new block: type=%d final=%d\n", d->btype, d->bfinal);
            #endif

            if (d->btype == 1) {
                /* build fixed huffman trees */
                tinf_build_fixed_trees(&d->ltree, &d->dtree);
            } else if (d->btype == 2) {
                /* decode trees from stream */
                res = tinf_decode_trees(d, &d->ltree, &d->dtree);
                if (res != TINF_OK) {
                    return res;
                }
            }
        }

        /* process current block */
        switch (d->btype)
        {
        case 0:
            /* decompress uncompressed block */
            res = tinf_inflate_uncompressed_block(d);
            break;
        case 1:
        case 2:
            /* decompress block with fixed/dynamic huffman trees */
            /* trees were decoded previously, so it's the same routine for both */
            res = tinf_inflate_block_data(d, &d->ltree, &d->dtree);
            break;
        default:
            return TINF_DATA_ERROR;
        }

        if (res == TINF_DONE && !d->bfinal) {
            /* the block has ended (without producing more data), but we
               can't return without data, so start procesing next block */
            goto next_blk;
        }

        if (res != TINF_OK) {
            return res;
        }

    } while (d->dest < d->dest_limit);

    return TINF_OK;
}