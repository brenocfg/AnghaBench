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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_11__ {TYPE_1__* cfg; } ;
typedef  TYPE_2__ lfs2_t ;
typedef  scalar_t__ lfs2_size_t ;
typedef  scalar_t__ lfs2_off_t ;
struct TYPE_12__ {scalar_t__ block; scalar_t__ off; scalar_t__ size; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_3__ lfs2_cache_t ;
typedef  scalar_t__ lfs2_block_t ;
struct TYPE_10__ {scalar_t__ block_size; scalar_t__ cache_size; int /*<<< orphan*/  prog_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  LFS2_ASSERT (int) ; 
 scalar_t__ LFS2_BLOCK_NULL ; 
 scalar_t__ lfs2_aligndown (scalar_t__,int /*<<< orphan*/ ) ; 
 int lfs2_bd_flush (TYPE_2__*,TYPE_3__*,TYPE_3__*,int) ; 
 scalar_t__ lfs2_max (scalar_t__,scalar_t__) ; 
 scalar_t__ lfs2_min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__) ; 

__attribute__((used)) static int lfs2_bd_prog(lfs2_t *lfs2,
        lfs2_cache_t *pcache, lfs2_cache_t *rcache, bool validate,
        lfs2_block_t block, lfs2_off_t off,
        const void *buffer, lfs2_size_t size) {
    const uint8_t *data = buffer;
    LFS2_ASSERT(block != LFS2_BLOCK_NULL);
    LFS2_ASSERT(off + size <= lfs2->cfg->block_size);

    while (size > 0) {
        if (block == pcache->block &&
                off >= pcache->off &&
                off < pcache->off + lfs2->cfg->cache_size) {
            // already fits in pcache?
            lfs2_size_t diff = lfs2_min(size,
                    lfs2->cfg->cache_size - (off-pcache->off));
            memcpy(&pcache->buffer[off-pcache->off], data, diff);

            data += diff;
            off += diff;
            size -= diff;

            pcache->size = lfs2_max(pcache->size, off - pcache->off);
            if (pcache->size == lfs2->cfg->cache_size) {
                // eagerly flush out pcache if we fill up
                int err = lfs2_bd_flush(lfs2, pcache, rcache, validate);
                if (err) {
                    return err;
                }
            }

            continue;
        }

        // pcache must have been flushed, either by programming and
        // entire block or manually flushing the pcache
        LFS2_ASSERT(pcache->block == LFS2_BLOCK_NULL);

        // prepare pcache, first condition can no longer fail
        pcache->block = block;
        pcache->off = lfs2_aligndown(off, lfs2->cfg->prog_size);
        pcache->size = 0;
    }

    return 0;
}