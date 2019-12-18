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
typedef  TYPE_2__ lfs1_t ;
typedef  int lfs1_ssize_t ;
typedef  scalar_t__ lfs1_size_t ;
struct TYPE_12__ {int flags; scalar_t__ pos; scalar_t__ size; scalar_t__ off; int /*<<< orphan*/  block; int /*<<< orphan*/  cache; int /*<<< orphan*/  head; } ;
typedef  TYPE_3__ lfs1_file_t ;
struct TYPE_10__ {scalar_t__ block_size; } ;

/* Variables and functions */
 int LFS1_ERR_BADF ; 
 int LFS1_F_READING ; 
 int LFS1_F_WRITING ; 
 int LFS1_O_WRONLY ; 
 int lfs1_cache_read (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int lfs1_ctz_find (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 
 int lfs1_file_flush (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ lfs1_min (scalar_t__,scalar_t__) ; 

lfs1_ssize_t lfs1_file_read(lfs1_t *lfs1, lfs1_file_t *file,
        void *buffer, lfs1_size_t size) {
    uint8_t *data = buffer;
    lfs1_size_t nsize = size;

    if ((file->flags & 3) == LFS1_O_WRONLY) {
        return LFS1_ERR_BADF;
    }

    if (file->flags & LFS1_F_WRITING) {
        // flush out any writes
        int err = lfs1_file_flush(lfs1, file);
        if (err) {
            return err;
        }
    }

    if (file->pos >= file->size) {
        // eof if past end
        return 0;
    }

    size = lfs1_min(size, file->size - file->pos);
    nsize = size;

    while (nsize > 0) {
        // check if we need a new block
        if (!(file->flags & LFS1_F_READING) ||
                file->off == lfs1->cfg->block_size) {
            int err = lfs1_ctz_find(lfs1, &file->cache, NULL,
                    file->head, file->size,
                    file->pos, &file->block, &file->off);
            if (err) {
                return err;
            }

            file->flags |= LFS1_F_READING;
        }

        // read as much as we can in current block
        lfs1_size_t diff = lfs1_min(nsize, lfs1->cfg->block_size - file->off);
        int err = lfs1_cache_read(lfs1, &file->cache, NULL,
                file->block, file->off, data, diff);
        if (err) {
            return err;
        }

        file->pos += diff;
        file->off += diff;
        data += diff;
        nsize -= diff;
    }

    return size;
}