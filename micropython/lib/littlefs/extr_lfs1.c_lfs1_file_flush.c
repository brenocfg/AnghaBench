#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_16__ {int block; } ;
struct TYPE_17__ {TYPE_12__ rcache; } ;
typedef  TYPE_1__ lfs1_t ;
typedef  scalar_t__ lfs1_ssize_t ;
typedef  int /*<<< orphan*/  lfs1_off_t ;
struct TYPE_18__ {int flags; int /*<<< orphan*/  pos; int /*<<< orphan*/  size; int /*<<< orphan*/  block; int /*<<< orphan*/  head; TYPE_12__ cache; } ;
typedef  TYPE_2__ lfs1_file_t ;

/* Variables and functions */
 int LFS1_ERR_CORRUPT ; 
 int LFS1_F_DIRTY ; 
 int LFS1_F_READING ; 
 int LFS1_F_WRITING ; 
 int LFS1_O_RDONLY ; 
 int /*<<< orphan*/  lfs1_cache_drop (TYPE_1__*,TYPE_12__*) ; 
 int lfs1_cache_flush (TYPE_1__*,TYPE_12__*,TYPE_12__*) ; 
 scalar_t__ lfs1_file_read (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int lfs1_file_relocate (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ lfs1_file_write (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int lfs1_file_flush(lfs1_t *lfs1, lfs1_file_t *file) {
    if (file->flags & LFS1_F_READING) {
        // just drop read cache
        lfs1_cache_drop(lfs1, &file->cache);
        file->flags &= ~LFS1_F_READING;
    }

    if (file->flags & LFS1_F_WRITING) {
        lfs1_off_t pos = file->pos;

        // copy over anything after current branch
        lfs1_file_t orig = {
            .head = file->head,
            .size = file->size,
            .flags = LFS1_O_RDONLY,
            .pos = file->pos,
            .cache = lfs1->rcache,
        };
        lfs1_cache_drop(lfs1, &lfs1->rcache);

        while (file->pos < file->size) {
            // copy over a byte at a time, leave it up to caching
            // to make this efficient
            uint8_t data;
            lfs1_ssize_t res = lfs1_file_read(lfs1, &orig, &data, 1);
            if (res < 0) {
                return res;
            }

            res = lfs1_file_write(lfs1, file, &data, 1);
            if (res < 0) {
                return res;
            }

            // keep our reference to the rcache in sync
            if (lfs1->rcache.block != 0xffffffff) {
                lfs1_cache_drop(lfs1, &orig.cache);
                lfs1_cache_drop(lfs1, &lfs1->rcache);
            }
        }

        // write out what we have
        while (true) {
            int err = lfs1_cache_flush(lfs1, &file->cache, &lfs1->rcache);
            if (err) {
                if (err == LFS1_ERR_CORRUPT) {
                    goto relocate;
                }
                return err;
            }

            break;
relocate:
            err = lfs1_file_relocate(lfs1, file);
            if (err) {
                return err;
            }
        }

        // actual file updates
        file->head = file->block;
        file->size = file->pos;
        file->flags &= ~LFS1_F_WRITING;
        file->flags |= LFS1_F_DIRTY;

        file->pos = pos;
    }

    return 0;
}