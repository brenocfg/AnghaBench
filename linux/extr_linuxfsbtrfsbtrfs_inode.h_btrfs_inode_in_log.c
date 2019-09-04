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
typedef  scalar_t__ u64 ;
struct TYPE_4__ {int /*<<< orphan*/  modified_extents; } ;
struct btrfs_inode {scalar_t__ logged_trans; scalar_t__ last_sub_trans; scalar_t__ last_log_commit; int /*<<< orphan*/  lock; TYPE_2__ extent_tree; TYPE_1__* root; } ;
struct TYPE_3__ {scalar_t__ last_log_commit; } ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int btrfs_inode_in_log(struct btrfs_inode *inode, u64 generation)
{
	int ret = 0;

	spin_lock(&inode->lock);
	if (inode->logged_trans == generation &&
	    inode->last_sub_trans <= inode->last_log_commit &&
	    inode->last_sub_trans <= inode->root->last_log_commit) {
		/*
		 * After a ranged fsync we might have left some extent maps
		 * (that fall outside the fsync's range). So return false
		 * here if the list isn't empty, to make sure btrfs_log_inode()
		 * will be called and process those extent maps.
		 */
		smp_mb();
		if (list_empty(&inode->extent_tree.modified_extents))
			ret = 1;
	}
	spin_unlock(&inode->lock);
	return ret;
}