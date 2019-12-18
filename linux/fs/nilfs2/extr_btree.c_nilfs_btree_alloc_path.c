#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* bpr_ptr; } ;
struct TYPE_3__ {void* bpr_ptr; } ;
struct nilfs_btree_path {int /*<<< orphan*/ * bp_op; TYPE_2__ bp_newreq; TYPE_1__ bp_oldreq; scalar_t__ bp_index; int /*<<< orphan*/ * bp_sib_bh; int /*<<< orphan*/ * bp_bh; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 void* NILFS_BMAP_INVALID_PTR ; 
 int NILFS_BTREE_LEVEL_DATA ; 
 int NILFS_BTREE_LEVEL_MAX ; 
 struct nilfs_btree_path* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_btree_path_cache ; 

__attribute__((used)) static struct nilfs_btree_path *nilfs_btree_alloc_path(void)
{
	struct nilfs_btree_path *path;
	int level = NILFS_BTREE_LEVEL_DATA;

	path = kmem_cache_alloc(nilfs_btree_path_cache, GFP_NOFS);
	if (path == NULL)
		goto out;

	for (; level < NILFS_BTREE_LEVEL_MAX; level++) {
		path[level].bp_bh = NULL;
		path[level].bp_sib_bh = NULL;
		path[level].bp_index = 0;
		path[level].bp_oldreq.bpr_ptr = NILFS_BMAP_INVALID_PTR;
		path[level].bp_newreq.bpr_ptr = NILFS_BMAP_INVALID_PTR;
		path[level].bp_op = NULL;
	}

out:
	return path;
}