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
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct ocfs2_inode_info {struct inode vfs_inode; int /*<<< orphan*/  ip_jinode; int /*<<< orphan*/  i_dquot; scalar_t__ i_datasync_tid; scalar_t__ i_sync_tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  jbd2_journal_init_jbd_inode (int /*<<< orphan*/ *,struct inode*) ; 
 struct ocfs2_inode_info* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocfs2_inode_cachep ; 

__attribute__((used)) static struct inode *ocfs2_alloc_inode(struct super_block *sb)
{
	struct ocfs2_inode_info *oi;

	oi = kmem_cache_alloc(ocfs2_inode_cachep, GFP_NOFS);
	if (!oi)
		return NULL;

	oi->i_sync_tid = 0;
	oi->i_datasync_tid = 0;
	memset(&oi->i_dquot, 0, sizeof(oi->i_dquot));

	jbd2_journal_init_jbd_inode(&oi->ip_jinode, &oi->vfs_inode);
	return &oi->vfs_inode;
}