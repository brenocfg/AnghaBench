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
struct nilfs_btree_path {int /*<<< orphan*/  bp_bh; } ;
struct nilfs_bmap {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_nilfs_volatile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_btree_abort_update_v (struct nilfs_bmap*,struct nilfs_btree_path*,int,struct inode*) ; 
 int nilfs_btree_height (struct nilfs_bmap*) ; 
 int nilfs_btree_prepare_update_v (struct nilfs_bmap*,struct nilfs_btree_path*,int,struct inode*) ; 

__attribute__((used)) static int nilfs_btree_prepare_propagate_v(struct nilfs_bmap *btree,
					   struct nilfs_btree_path *path,
					   int minlevel, int *maxlevelp,
					   struct inode *dat)
{
	int level, ret;

	level = minlevel;
	if (!buffer_nilfs_volatile(path[level].bp_bh)) {
		ret = nilfs_btree_prepare_update_v(btree, path, level, dat);
		if (ret < 0)
			return ret;
	}
	while ((++level < nilfs_btree_height(btree) - 1) &&
	       !buffer_dirty(path[level].bp_bh)) {

		WARN_ON(buffer_nilfs_volatile(path[level].bp_bh));
		ret = nilfs_btree_prepare_update_v(btree, path, level, dat);
		if (ret < 0)
			goto out;
	}

	/* success */
	*maxlevelp = level - 1;
	return 0;

	/* error */
 out:
	while (--level > minlevel)
		nilfs_btree_abort_update_v(btree, path, level, dat);
	if (!buffer_nilfs_volatile(path[level].bp_bh))
		nilfs_btree_abort_update_v(btree, path, level, dat);
	return ret;
}