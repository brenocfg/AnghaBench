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
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct dentry {int /*<<< orphan*/  d_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_STATE_NEWENTRY ; 
 struct dentry* d_find_any_alias (struct inode*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  ext4_clear_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_test_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 struct inode* igrab (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int sync_inode_metadata (struct inode*,int) ; 
 int sync_mapping_buffers (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_sync_parent(struct inode *inode)
{
	struct dentry *dentry = NULL;
	struct inode *next;
	int ret = 0;

	if (!ext4_test_inode_state(inode, EXT4_STATE_NEWENTRY))
		return 0;
	inode = igrab(inode);
	while (ext4_test_inode_state(inode, EXT4_STATE_NEWENTRY)) {
		ext4_clear_inode_state(inode, EXT4_STATE_NEWENTRY);
		dentry = d_find_any_alias(inode);
		if (!dentry)
			break;
		next = igrab(d_inode(dentry->d_parent));
		dput(dentry);
		if (!next)
			break;
		iput(inode);
		inode = next;
		/*
		 * The directory inode may have gone through rmdir by now. But
		 * the inode itself and its blocks are still allocated (we hold
		 * a reference to the inode so it didn't go through
		 * ext4_evict_inode()) and so we are safe to flush metadata
		 * blocks and the inode.
		 */
		ret = sync_mapping_buffers(inode->i_mapping);
		if (ret)
			break;
		ret = sync_inode_metadata(inode, 1);
		if (ret)
			break;
	}
	iput(inode);
	return ret;
}