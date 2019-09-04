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
struct list_head {int dummy; } ;
struct inode {int dummy; } ;
struct fsync_inode_entry {int /*<<< orphan*/  list; struct inode* inode; } ;
struct f2fs_sb_info {int /*<<< orphan*/  sb; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 struct fsync_inode_entry* ERR_CAST (struct inode*) ; 
 struct fsync_inode_entry* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_F2FS_ZERO ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int dquot_alloc_inode (struct inode*) ; 
 int dquot_initialize (struct inode*) ; 
 struct inode* f2fs_iget_retry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fsync_inode_entry* f2fs_kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsync_entry_slab ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static struct fsync_inode_entry *add_fsync_inode(struct f2fs_sb_info *sbi,
			struct list_head *head, nid_t ino, bool quota_inode)
{
	struct inode *inode;
	struct fsync_inode_entry *entry;
	int err;

	inode = f2fs_iget_retry(sbi->sb, ino);
	if (IS_ERR(inode))
		return ERR_CAST(inode);

	err = dquot_initialize(inode);
	if (err)
		goto err_out;

	if (quota_inode) {
		err = dquot_alloc_inode(inode);
		if (err)
			goto err_out;
	}

	entry = f2fs_kmem_cache_alloc(fsync_entry_slab, GFP_F2FS_ZERO);
	entry->inode = inode;
	list_add_tail(&entry->list, head);

	return entry;
err_out:
	iput(inode);
	return ERR_PTR(err);
}