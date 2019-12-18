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
struct inode {int dummy; } ;
struct ufs_inode_info {struct inode vfs_inode; int /*<<< orphan*/  truncate_mutex; int /*<<< orphan*/  meta_lock; } ;
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  inode_set_iversion (struct inode*,int) ; 
 struct ufs_inode_info* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seqlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ufs_inode_cachep ; 

__attribute__((used)) static struct inode *ufs_alloc_inode(struct super_block *sb)
{
	struct ufs_inode_info *ei;

	ei = kmem_cache_alloc(ufs_inode_cachep, GFP_NOFS);
	if (!ei)
		return NULL;

	inode_set_iversion(&ei->vfs_inode, 1);
	seqlock_init(&ei->meta_lock);
	mutex_init(&ei->truncate_mutex);
	return &ei->vfs_inode;
}