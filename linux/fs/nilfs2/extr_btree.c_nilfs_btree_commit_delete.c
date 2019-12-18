#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nilfs_btree_path {int /*<<< orphan*/  (* bp_op ) (struct nilfs_bmap*,struct nilfs_btree_path*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  bp_oldreq; } ;
struct nilfs_bmap {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int NILFS_BTREE_LEVEL_NODE_MIN ; 
 int /*<<< orphan*/  nilfs_bmap_commit_end_ptr (struct nilfs_bmap*,int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  nilfs_bmap_dirty (struct nilfs_bmap*) ; 
 int /*<<< orphan*/  nilfs_bmap_set_dirty (struct nilfs_bmap*) ; 
 int /*<<< orphan*/  stub1 (struct nilfs_bmap*,struct nilfs_btree_path*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nilfs_btree_commit_delete(struct nilfs_bmap *btree,
				      struct nilfs_btree_path *path,
				      int maxlevel, struct inode *dat)
{
	int level;

	for (level = NILFS_BTREE_LEVEL_NODE_MIN; level <= maxlevel; level++) {
		nilfs_bmap_commit_end_ptr(btree, &path[level].bp_oldreq, dat);
		path[level].bp_op(btree, path, level, NULL, NULL);
	}

	if (!nilfs_bmap_dirty(btree))
		nilfs_bmap_set_dirty(btree);
}