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
struct ext4_inode_info {struct inode vfs_inode; int /*<<< orphan*/  i_rsv_conversion_work; int /*<<< orphan*/  i_unwritten; scalar_t__ i_datasync_tid; scalar_t__ i_sync_tid; int /*<<< orphan*/  i_completed_io_lock; int /*<<< orphan*/  i_rsv_conversion_list; int /*<<< orphan*/ * jinode; int /*<<< orphan*/  i_dquot; scalar_t__ i_reserved_quota; int /*<<< orphan*/  i_pending_tree; int /*<<< orphan*/  i_block_reservation_lock; scalar_t__ i_da_metadata_calc_last_lblock; scalar_t__ i_da_metadata_calc_len; scalar_t__ i_reserved_data_blocks; scalar_t__ i_es_shrink_lblk; scalar_t__ i_es_shk_nr; scalar_t__ i_es_all_nr; int /*<<< orphan*/  i_es_list; int /*<<< orphan*/  i_es_lock; int /*<<< orphan*/  i_es_tree; int /*<<< orphan*/  i_prealloc_lock; int /*<<< orphan*/  i_prealloc_list; int /*<<< orphan*/  i_raw_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_end_io_rsv_work ; 
 int /*<<< orphan*/  ext4_es_init_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_init_pending_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_inode_cachep ; 
 int /*<<< orphan*/  inode_set_iversion (struct inode*,int) ; 
 struct ext4_inode_info* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct inode *ext4_alloc_inode(struct super_block *sb)
{
	struct ext4_inode_info *ei;

	ei = kmem_cache_alloc(ext4_inode_cachep, GFP_NOFS);
	if (!ei)
		return NULL;

	inode_set_iversion(&ei->vfs_inode, 1);
	spin_lock_init(&ei->i_raw_lock);
	INIT_LIST_HEAD(&ei->i_prealloc_list);
	spin_lock_init(&ei->i_prealloc_lock);
	ext4_es_init_tree(&ei->i_es_tree);
	rwlock_init(&ei->i_es_lock);
	INIT_LIST_HEAD(&ei->i_es_list);
	ei->i_es_all_nr = 0;
	ei->i_es_shk_nr = 0;
	ei->i_es_shrink_lblk = 0;
	ei->i_reserved_data_blocks = 0;
	ei->i_da_metadata_calc_len = 0;
	ei->i_da_metadata_calc_last_lblock = 0;
	spin_lock_init(&(ei->i_block_reservation_lock));
	ext4_init_pending_tree(&ei->i_pending_tree);
#ifdef CONFIG_QUOTA
	ei->i_reserved_quota = 0;
	memset(&ei->i_dquot, 0, sizeof(ei->i_dquot));
#endif
	ei->jinode = NULL;
	INIT_LIST_HEAD(&ei->i_rsv_conversion_list);
	spin_lock_init(&ei->i_completed_io_lock);
	ei->i_sync_tid = 0;
	ei->i_datasync_tid = 0;
	atomic_set(&ei->i_unwritten, 0);
	INIT_WORK(&ei->i_rsv_conversion_work, ext4_end_io_rsv_work);
	return &ei->vfs_inode;
}