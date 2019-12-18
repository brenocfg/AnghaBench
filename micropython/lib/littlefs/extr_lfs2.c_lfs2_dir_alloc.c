#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  rcache; } ;
typedef  TYPE_1__ lfs2_t ;
struct TYPE_8__ {int rev; int off; int erased; int split; void** tail; scalar_t__ count; void* etag; int /*<<< orphan*/ * pair; } ;
typedef  TYPE_2__ lfs2_mdir_t ;

/* Variables and functions */
 void* LFS2_BLOCK_NULL ; 
 int LFS2_ERR_CORRUPT ; 
 int lfs2_alloc (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int lfs2_bd_read (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int lfs2_fromle32 (int) ; 

__attribute__((used)) static int lfs2_dir_alloc(lfs2_t *lfs2, lfs2_mdir_t *dir) {
    // allocate pair of dir blocks (backwards, so we write block 1 first)
    for (int i = 0; i < 2; i++) {
        int err = lfs2_alloc(lfs2, &dir->pair[(i+1)%2]);
        if (err) {
            return err;
        }
    }

    // rather than clobbering one of the blocks we just pretend
    // the revision may be valid
    int err = lfs2_bd_read(lfs2,
            NULL, &lfs2->rcache, sizeof(dir->rev),
            dir->pair[0], 0, &dir->rev, sizeof(dir->rev));
    dir->rev = lfs2_fromle32(dir->rev);
    if (err && err != LFS2_ERR_CORRUPT) {
        return err;
    }

    // make sure we don't immediately evict
    dir->rev += dir->rev & 1;

    // set defaults
    dir->off = sizeof(dir->rev);
    dir->etag = LFS2_BLOCK_NULL;
    dir->count = 0;
    dir->tail[0] = LFS2_BLOCK_NULL;
    dir->tail[1] = LFS2_BLOCK_NULL;
    dir->erased = false;
    dir->split = false;

    // don't write out yet, let caller take care of that
    return 0;
}