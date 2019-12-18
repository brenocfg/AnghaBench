#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lfs2_fs_parent_match {int /*<<< orphan*/  pair; TYPE_2__* lfs2; } ;
struct lfs2_diskoff {int /*<<< orphan*/  off; int /*<<< orphan*/  block; } ;
typedef  int /*<<< orphan*/  lfs2_tag_t ;
struct TYPE_5__ {TYPE_1__* cfg; int /*<<< orphan*/  rcache; int /*<<< orphan*/  pcache; } ;
typedef  TYPE_2__ lfs2_t ;
typedef  int /*<<< orphan*/  lfs2_block_t ;
typedef  int /*<<< orphan*/  child ;
struct TYPE_4__ {int /*<<< orphan*/  block_size; } ;

/* Variables and functions */
 int LFS2_CMP_EQ ; 
 int LFS2_CMP_LT ; 
 int lfs2_bd_read (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 scalar_t__ lfs2_pair_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lfs2_pair_fromle32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lfs2_fs_parent_match(void *data,
        lfs2_tag_t tag, const void *buffer) {
    struct lfs2_fs_parent_match *find = data;
    lfs2_t *lfs2 = find->lfs2;
    const struct lfs2_diskoff *disk = buffer;
    (void)tag;

    lfs2_block_t child[2];
    int err = lfs2_bd_read(lfs2,
            &lfs2->pcache, &lfs2->rcache, lfs2->cfg->block_size,
            disk->block, disk->off, &child, sizeof(child));
    if (err) {
        return err;
    }

    lfs2_pair_fromle32(child);
    return (lfs2_pair_cmp(child, find->pair) == 0) ? LFS2_CMP_EQ : LFS2_CMP_LT;
}