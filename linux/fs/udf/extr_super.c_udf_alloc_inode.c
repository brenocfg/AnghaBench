#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_2__ {int lstart; } ;
struct udf_inode_info {struct inode vfs_inode; int /*<<< orphan*/  i_extent_cache_lock; TYPE_1__ cached_extent; int /*<<< orphan*/  i_data_sem; scalar_t__ i_streamdir; scalar_t__ i_strat4096; scalar_t__ i_next_alloc_goal; scalar_t__ i_next_alloc_block; scalar_t__ i_lenStreams; scalar_t__ i_lenExtents; scalar_t__ i_unique; } ;
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 struct udf_inode_info* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udf_inode_cachep ; 

__attribute__((used)) static struct inode *udf_alloc_inode(struct super_block *sb)
{
	struct udf_inode_info *ei;
	ei = kmem_cache_alloc(udf_inode_cachep, GFP_KERNEL);
	if (!ei)
		return NULL;

	ei->i_unique = 0;
	ei->i_lenExtents = 0;
	ei->i_lenStreams = 0;
	ei->i_next_alloc_block = 0;
	ei->i_next_alloc_goal = 0;
	ei->i_strat4096 = 0;
	ei->i_streamdir = 0;
	init_rwsem(&ei->i_data_sem);
	ei->cached_extent.lstart = -1;
	spin_lock_init(&ei->i_extent_cache_lock);

	return &ei->vfs_inode;
}