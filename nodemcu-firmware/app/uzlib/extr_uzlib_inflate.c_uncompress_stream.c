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
struct TYPE_8__ {int bType; int /*<<< orphan*/  bFinal; int /*<<< orphan*/  dtree; int /*<<< orphan*/  ltree; scalar_t__ destSize; } ;
typedef  TYPE_1__ UZLIB_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PRINT (char*,int,int /*<<< orphan*/ ) ; 
 int UZLIB_DATA_ERROR ; 
 int UZLIB_DONE ; 
 int UZLIB_OK ; 
 int /*<<< orphan*/  build_fixed_trees (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int decode_trees (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getbit (TYPE_1__*) ; 
 int inflate_block_data (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int inflate_uncompressed_block (TYPE_1__*) ; 
 int read_bits (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uncompress_stream (UZLIB_DATA *d) {
  do {
    int res;

    /* start a new block */
    if (d->bType == -1) {
      next_blk:
      /* read final block flag */
      d->bFinal = getbit(d);
      /* read block type (2 bits) */
      d->bType = read_bits(d, 2, 0);

      DBG_PRINT("Started new block: type=%d final=%d\n", d->bType, d->bFinal);

      if (d->bType == 1) {
        /* build fixed huffman trees */
        build_fixed_trees(&d->ltree, &d->dtree);
      } else if (d->bType == 2) {
        /* decode trees from stream */
        res = decode_trees(d, &d->ltree, &d->dtree);
        if (res != UZLIB_OK)
          return res;
      }
    }

    /* process current block */
    switch (d->bType) {
    case 0:
      /* decompress uncompressed block */
      res = inflate_uncompressed_block(d);
      break;
    case 1:
    case 2:
      /* decompress block with fixed or dynamic huffman trees.  These */
      /* trees were decoded previously, so it's the same routine for both */
      res = inflate_block_data(d, &d->ltree, &d->dtree);
      break;
    default:
      return UZLIB_DATA_ERROR;
    }

    if (res == UZLIB_DONE && !d->bFinal) {
      /* the block has ended (without producing more data), but we
         can't return without data, so start procesing next block */
      goto next_blk;
    }

    if (res != UZLIB_OK)
      return res;

  } while (--d->destSize);

  return UZLIB_OK;
}