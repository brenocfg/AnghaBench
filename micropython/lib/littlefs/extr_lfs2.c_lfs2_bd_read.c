#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {TYPE_3__* cfg; } ;
typedef  TYPE_1__ lfs2_t ;
typedef  scalar_t__ lfs2_size_t ;
typedef  scalar_t__ lfs2_off_t ;
struct TYPE_8__ {scalar_t__ block; scalar_t__ off; scalar_t__ size; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_2__ lfs2_cache_t ;
typedef  scalar_t__ lfs2_block_t ;
struct TYPE_9__ {scalar_t__ block_size; scalar_t__ block_count; scalar_t__ cache_size; int (* read ) (TYPE_3__*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ;int /*<<< orphan*/  read_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  LFS2_ASSERT (int) ; 
 scalar_t__ LFS2_BLOCK_NULL ; 
 int LFS2_ERR_CORRUPT ; 
 scalar_t__ lfs2_aligndown (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ lfs2_alignup (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ lfs2_min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int stub1 (TYPE_3__*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int lfs2_bd_read(lfs2_t *lfs2,
        const lfs2_cache_t *pcache, lfs2_cache_t *rcache, lfs2_size_t hint,
        lfs2_block_t block, lfs2_off_t off,
        void *buffer, lfs2_size_t size) {
    uint8_t *data = buffer;
    LFS2_ASSERT(block != LFS2_BLOCK_NULL);
    if (off+size > lfs2->cfg->block_size) {
        return LFS2_ERR_CORRUPT;
    }

    while (size > 0) {
        lfs2_size_t diff = size;

        if (pcache && block == pcache->block &&
                off < pcache->off + pcache->size) {
            if (off >= pcache->off) {
                // is already in pcache?
                diff = lfs2_min(diff, pcache->size - (off-pcache->off));
                memcpy(data, &pcache->buffer[off-pcache->off], diff);

                data += diff;
                off += diff;
                size -= diff;
                continue;
            }

            // pcache takes priority
            diff = lfs2_min(diff, pcache->off-off);
        }

        if (block == rcache->block &&
                off < rcache->off + rcache->size) {
            if (off >= rcache->off) {
                // is already in rcache?
                diff = lfs2_min(diff, rcache->size - (off-rcache->off));
                memcpy(data, &rcache->buffer[off-rcache->off], diff);

                data += diff;
                off += diff;
                size -= diff;
                continue;
            }

            // rcache takes priority
            diff = lfs2_min(diff, rcache->off-off);
        }

        // load to cache, first condition can no longer fail
        LFS2_ASSERT(block < lfs2->cfg->block_count);
        rcache->block = block;
        rcache->off = lfs2_aligndown(off, lfs2->cfg->read_size);
        rcache->size = lfs2_min(
                lfs2_min(
                    lfs2_alignup(off+hint, lfs2->cfg->read_size),
                    lfs2->cfg->block_size)
                - rcache->off,
                lfs2->cfg->cache_size);
        int err = lfs2->cfg->read(lfs2->cfg, rcache->block,
                rcache->off, rcache->buffer, rcache->size);
        LFS2_ASSERT(err <= 0);
        if (err) {
            return err;
        }
    }

    return 0;
}