#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {TYPE_3__* cfg; } ;
typedef  TYPE_1__ lfs1_t ;
typedef  scalar_t__ lfs1_size_t ;
typedef  scalar_t__ lfs1_off_t ;
struct TYPE_9__ {scalar_t__ block; scalar_t__ off; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_2__ lfs1_cache_t ;
typedef  scalar_t__ lfs1_block_t ;
struct TYPE_10__ {scalar_t__ block_count; scalar_t__ prog_size; scalar_t__ read_size; int (* read ) (TYPE_3__*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LFS1_ASSERT (int) ; 
 scalar_t__ lfs1_min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int stub1 (TYPE_3__*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int stub2 (TYPE_3__*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int lfs1_cache_read(lfs1_t *lfs1, lfs1_cache_t *rcache,
        const lfs1_cache_t *pcache, lfs1_block_t block,
        lfs1_off_t off, void *buffer, lfs1_size_t size) {
    uint8_t *data = buffer;
    LFS1_ASSERT(block < lfs1->cfg->block_count);

    while (size > 0) {
        if (pcache && block == pcache->block && off >= pcache->off &&
                off < pcache->off + lfs1->cfg->prog_size) {
            // is already in pcache?
            lfs1_size_t diff = lfs1_min(size,
                    lfs1->cfg->prog_size - (off-pcache->off));
            memcpy(data, &pcache->buffer[off-pcache->off], diff);

            data += diff;
            off += diff;
            size -= diff;
            continue;
        }

        if (block == rcache->block && off >= rcache->off &&
                off < rcache->off + lfs1->cfg->read_size) {
            // is already in rcache?
            lfs1_size_t diff = lfs1_min(size,
                    lfs1->cfg->read_size - (off-rcache->off));
            memcpy(data, &rcache->buffer[off-rcache->off], diff);

            data += diff;
            off += diff;
            size -= diff;
            continue;
        }

        if (off % lfs1->cfg->read_size == 0 && size >= lfs1->cfg->read_size) {
            // bypass cache?
            lfs1_size_t diff = size - (size % lfs1->cfg->read_size);
            int err = lfs1->cfg->read(lfs1->cfg, block, off, data, diff);
            if (err) {
                return err;
            }

            data += diff;
            off += diff;
            size -= diff;
            continue;
        }

        // load to cache, first condition can no longer fail
        rcache->block = block;
        rcache->off = off - (off % lfs1->cfg->read_size);
        int err = lfs1->cfg->read(lfs1->cfg, rcache->block,
                rcache->off, rcache->buffer, lfs1->cfg->read_size);
        if (err) {
            return err;
        }
    }

    return 0;
}