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
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fs_id; int /*<<< orphan*/  khandle; } ;
struct orangefs_inode_s {struct inode vfs_inode; int /*<<< orphan*/ * link_target; scalar_t__ last_failed_block_index_read; TYPE_1__ refn; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GOSSIP_SUPER_DEBUG ; 
 int /*<<< orphan*/  ORANGEFS_FS_ID_NULL ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,struct inode*) ; 
 struct orangefs_inode_s* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  orangefs_inode_cache ; 

__attribute__((used)) static struct inode *orangefs_alloc_inode(struct super_block *sb)
{
	struct orangefs_inode_s *orangefs_inode;

	orangefs_inode = kmem_cache_alloc(orangefs_inode_cache, GFP_KERNEL);
	if (!orangefs_inode)
		return NULL;

	/*
	 * We want to clear everything except for rw_semaphore and the
	 * vfs_inode.
	 */
	memset(&orangefs_inode->refn.khandle, 0, 16);
	orangefs_inode->refn.fs_id = ORANGEFS_FS_ID_NULL;
	orangefs_inode->last_failed_block_index_read = 0;
	memset(orangefs_inode->link_target, 0, sizeof(orangefs_inode->link_target));

	gossip_debug(GOSSIP_SUPER_DEBUG,
		     "orangefs_alloc_inode: allocated %p\n",
		     &orangefs_inode->vfs_inode);
	return &orangefs_inode->vfs_inode;
}