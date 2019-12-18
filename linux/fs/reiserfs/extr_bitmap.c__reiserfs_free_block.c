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
struct reiserfs_transaction_handle {int /*<<< orphan*/  t_trans_id; struct super_block* t_super; } ;
struct reiserfs_super_block {int dummy; } ;
struct reiserfs_bitmap_info {int /*<<< orphan*/  free_count; } ;
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  int /*<<< orphan*/  b_blocknr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PROC_INFO_INC (struct super_block*,int /*<<< orphan*/ ) ; 
 struct reiserfs_bitmap_info* SB_AP_BITMAP (struct super_block*) ; 
 struct buffer_head* SB_BUFFER_WITH_SB (struct super_block*) ; 
 struct reiserfs_super_block* SB_DISK_SUPER_BLOCK (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  dquot_free_block_nodirty (struct inode*,int) ; 
 int /*<<< orphan*/  free_block ; 
 int /*<<< orphan*/  get_bit_address (struct super_block*,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  journal_mark_dirty (struct reiserfs_transaction_handle*,struct buffer_head*) ; 
 unsigned int reiserfs_bmap_count (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_error (struct super_block*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_prepare_for_journal (struct super_block*,struct buffer_head*,int) ; 
 struct buffer_head* reiserfs_read_bitmap_block (struct super_block*,unsigned int) ; 
 int /*<<< orphan*/  reiserfs_test_and_clear_le_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_write_lock_nested (struct super_block*,int) ; 
 int reiserfs_write_unlock_nested (struct super_block*) ; 
 scalar_t__ sb_free_blocks (struct reiserfs_super_block*) ; 
 int /*<<< orphan*/  set_sb_free_blocks (struct reiserfs_super_block*,scalar_t__) ; 

__attribute__((used)) static void _reiserfs_free_block(struct reiserfs_transaction_handle *th,
				 struct inode *inode, b_blocknr_t block,
				 int for_unformatted)
{
	struct super_block *s = th->t_super;
	struct reiserfs_super_block *rs;
	struct buffer_head *sbh, *bmbh;
	struct reiserfs_bitmap_info *apbi;
	unsigned int nr, offset;

	BUG_ON(!th->t_trans_id);
	PROC_INFO_INC(s, free_block);
	rs = SB_DISK_SUPER_BLOCK(s);
	sbh = SB_BUFFER_WITH_SB(s);
	apbi = SB_AP_BITMAP(s);

	get_bit_address(s, block, &nr, &offset);

	if (nr >= reiserfs_bmap_count(s)) {
		reiserfs_error(s, "vs-4075", "block %lu is out of range",
			       block);
		return;
	}

	bmbh = reiserfs_read_bitmap_block(s, nr);
	if (!bmbh)
		return;

	reiserfs_prepare_for_journal(s, bmbh, 1);

	/* clear bit for the given block in bit map */
	if (!reiserfs_test_and_clear_le_bit(offset, bmbh->b_data)) {
		reiserfs_error(s, "vs-4080",
			       "block %lu: bit already cleared", block);
	}
	apbi[nr].free_count++;
	journal_mark_dirty(th, bmbh);
	brelse(bmbh);

	reiserfs_prepare_for_journal(s, sbh, 1);
	/* update super block */
	set_sb_free_blocks(rs, sb_free_blocks(rs) + 1);

	journal_mark_dirty(th, sbh);
	if (for_unformatted) {
		int depth = reiserfs_write_unlock_nested(s);
		dquot_free_block_nodirty(inode, 1);
		reiserfs_write_lock_nested(s, depth);
	}
}