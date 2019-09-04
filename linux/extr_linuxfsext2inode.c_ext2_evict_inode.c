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
struct inode {int /*<<< orphan*/  i_sb; scalar_t__ i_blocks; scalar_t__ i_size; int /*<<< orphan*/  i_data; int /*<<< orphan*/  i_nlink; } ;
struct ext2_block_alloc_info {int dummy; } ;
struct TYPE_2__ {struct ext2_block_alloc_info* i_block_alloc_info; int /*<<< orphan*/  i_dtime; } ;

/* Variables and functions */
 TYPE_1__* EXT2_I (struct inode*) ; 
 int /*<<< orphan*/  __ext2_write_inode (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  dquot_drop (struct inode*) ; 
 int /*<<< orphan*/  dquot_initialize (struct inode*) ; 
 int /*<<< orphan*/  ext2_discard_reservation (struct inode*) ; 
 int /*<<< orphan*/  ext2_free_inode (struct inode*) ; 
 int /*<<< orphan*/  ext2_truncate_blocks (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2_xattr_delete_inode (struct inode*) ; 
 int /*<<< orphan*/  inode_needs_sync (struct inode*) ; 
 int /*<<< orphan*/  invalidate_inode_buffers (struct inode*) ; 
 int /*<<< orphan*/  is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ext2_block_alloc_info*) ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  sb_end_intwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_intwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (struct ext2_block_alloc_info*) ; 

void ext2_evict_inode(struct inode * inode)
{
	struct ext2_block_alloc_info *rsv;
	int want_delete = 0;

	if (!inode->i_nlink && !is_bad_inode(inode)) {
		want_delete = 1;
		dquot_initialize(inode);
	} else {
		dquot_drop(inode);
	}

	truncate_inode_pages_final(&inode->i_data);

	if (want_delete) {
		sb_start_intwrite(inode->i_sb);
		/* set dtime */
		EXT2_I(inode)->i_dtime	= ktime_get_real_seconds();
		mark_inode_dirty(inode);
		__ext2_write_inode(inode, inode_needs_sync(inode));
		/* truncate to 0 */
		inode->i_size = 0;
		if (inode->i_blocks)
			ext2_truncate_blocks(inode, 0);
		ext2_xattr_delete_inode(inode);
	}

	invalidate_inode_buffers(inode);
	clear_inode(inode);

	ext2_discard_reservation(inode);
	rsv = EXT2_I(inode)->i_block_alloc_info;
	EXT2_I(inode)->i_block_alloc_info = NULL;
	if (unlikely(rsv))
		kfree(rsv);

	if (want_delete) {
		ext2_free_inode(inode);
		sb_end_intwrite(inode->i_sb);
	}
}