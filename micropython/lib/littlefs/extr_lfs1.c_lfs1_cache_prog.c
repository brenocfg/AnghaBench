#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_12__ {TYPE_3__* cfg; } ;
typedef  TYPE_1__ lfs1_t ;
typedef  int lfs1_size_t ;
typedef  size_t lfs1_off_t ;
struct TYPE_13__ {int block; size_t off; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_2__ lfs1_cache_t ;
typedef  int lfs1_block_t ;
struct TYPE_14__ {int block_count; size_t prog_size; int (* prog ) (TYPE_3__*,int,size_t,int /*<<< orphan*/  const*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LFS1_ASSERT (int) ; 
 int LFS1_ERR_CORRUPT ; 
 int lfs1_cache_cmp (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/  const*,int) ; 
 int lfs1_cache_flush (TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 
 int lfs1_min (int,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int stub1 (TYPE_3__*,int,size_t,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int lfs1_cache_prog(lfs1_t *lfs1, lfs1_cache_t *pcache,
        lfs1_cache_t *rcache, lfs1_block_t block,
        lfs1_off_t off, const void *buffer, lfs1_size_t size) {
    const uint8_t *data = buffer;
    LFS1_ASSERT(block < lfs1->cfg->block_count);

    while (size > 0) {
        if (block == pcache->block && off >= pcache->off &&
                off < pcache->off + lfs1->cfg->prog_size) {
            // is already in pcache?
            lfs1_size_t diff = lfs1_min(size,
                    lfs1->cfg->prog_size - (off-pcache->off));
            memcpy(&pcache->buffer[off-pcache->off], data, diff);

            data += diff;
            off += diff;
            size -= diff;

            if (off % lfs1->cfg->prog_size == 0) {
                // eagerly flush out pcache if we fill up
                int err = lfs1_cache_flush(lfs1, pcache, rcache);
                if (err) {
                    return err;
                }
            }

            continue;
        }

        // pcache must have been flushed, either by programming and
        // entire block or manually flushing the pcache
        LFS1_ASSERT(pcache->block == 0xffffffff);

        if (off % lfs1->cfg->prog_size == 0 &&
                size >= lfs1->cfg->prog_size) {
            // bypass pcache?
            lfs1_size_t diff = size - (size % lfs1->cfg->prog_size);
            int err = lfs1->cfg->prog(lfs1->cfg, block, off, data, diff);
            if (err) {
                return err;
            }

            if (rcache) {
                int res = lfs1_cache_cmp(lfs1, rcache, NULL,
                        block, off, data, diff);
                if (res < 0) {
                    return res;
                }

                if (!res) {
                    return LFS1_ERR_CORRUPT;
                }
            }

            data += diff;
            off += diff;
            size -= diff;
            continue;
        }

        // prepare pcache, first condition can no longer fail
        pcache->block = block;
        pcache->off = off - (off % lfs1->cfg->prog_size);
    }

    return 0;
}