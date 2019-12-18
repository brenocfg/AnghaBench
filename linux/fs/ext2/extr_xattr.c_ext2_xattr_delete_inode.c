#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct ext2_sb_info {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_blocknr; int /*<<< orphan*/  b_count; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_5__ {int /*<<< orphan*/  xattr_sem; scalar_t__ i_file_acl; } ;
struct TYPE_4__ {scalar_t__ h_refcount; scalar_t__ h_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  EA_BLOCK_CACHE (struct inode*) ; 
 TYPE_3__* EXT2_I (struct inode*) ; 
 struct ext2_sb_info* EXT2_SB (int /*<<< orphan*/ ) ; 
 TYPE_1__* HDR (struct buffer_head*) ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bforget (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ cpu_to_le32 (int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dquot_free_block_nodirty (struct inode*,int) ; 
 int /*<<< orphan*/  ea_bdebug (struct buffer_head*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2_data_block_valid (struct ext2_sb_info*,scalar_t__,int) ; 
 int /*<<< orphan*/  ext2_error (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ext2_free_blocks (struct inode*,scalar_t__,int) ; 
 int /*<<< orphan*/  ext2_xattr_header_valid (TYPE_1__*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  le32_add_cpu (scalar_t__*,int) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  mb_cache_entry_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_bread (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sync_dirty_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void
ext2_xattr_delete_inode(struct inode *inode)
{
	struct buffer_head *bh = NULL;
	struct ext2_sb_info *sbi = EXT2_SB(inode->i_sb);

	down_write(&EXT2_I(inode)->xattr_sem);
	if (!EXT2_I(inode)->i_file_acl)
		goto cleanup;

	if (!ext2_data_block_valid(sbi, EXT2_I(inode)->i_file_acl, 1)) {
		ext2_error(inode->i_sb, "ext2_xattr_delete_inode",
			"inode %ld: xattr block %d is out of data blocks range",
			inode->i_ino, EXT2_I(inode)->i_file_acl);
		goto cleanup;
	}

	bh = sb_bread(inode->i_sb, EXT2_I(inode)->i_file_acl);
	if (!bh) {
		ext2_error(inode->i_sb, "ext2_xattr_delete_inode",
			"inode %ld: block %d read error", inode->i_ino,
			EXT2_I(inode)->i_file_acl);
		goto cleanup;
	}
	ea_bdebug(bh, "b_count=%d", atomic_read(&(bh->b_count)));
	if (!ext2_xattr_header_valid(HDR(bh))) {
		ext2_error(inode->i_sb, "ext2_xattr_delete_inode",
			"inode %ld: bad block %d", inode->i_ino,
			EXT2_I(inode)->i_file_acl);
		goto cleanup;
	}
	lock_buffer(bh);
	if (HDR(bh)->h_refcount == cpu_to_le32(1)) {
		__u32 hash = le32_to_cpu(HDR(bh)->h_hash);

		/*
		 * This must happen under buffer lock for ext2_xattr_set2() to
		 * reliably detect freed block
		 */
		mb_cache_entry_delete(EA_BLOCK_CACHE(inode), hash,
				      bh->b_blocknr);
		ext2_free_blocks(inode, EXT2_I(inode)->i_file_acl, 1);
		get_bh(bh);
		bforget(bh);
		unlock_buffer(bh);
	} else {
		le32_add_cpu(&HDR(bh)->h_refcount, -1);
		ea_bdebug(bh, "refcount now=%d",
			le32_to_cpu(HDR(bh)->h_refcount));
		unlock_buffer(bh);
		mark_buffer_dirty(bh);
		if (IS_SYNC(inode))
			sync_dirty_buffer(bh);
		dquot_free_block_nodirty(inode, 1);
	}
	EXT2_I(inode)->i_file_acl = 0;

cleanup:
	brelse(bh);
	up_write(&EXT2_I(inode)->xattr_sem);
}