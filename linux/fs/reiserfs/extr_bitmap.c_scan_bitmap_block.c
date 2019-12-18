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
struct reiserfs_transaction_handle {int /*<<< orphan*/  t_trans_id; struct super_block* t_super; } ;
struct reiserfs_bitmap_info {int free_count; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  stolen; int /*<<< orphan*/  bmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PROC_INFO_INC (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_SB_FREE_BLOCKS (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  RFALSE (int,char*,unsigned int,int) ; 
 struct reiserfs_bitmap_info* SB_AP_BITMAP (struct super_block*) ; 
 struct buffer_head* SB_BUFFER_WITH_SB (struct super_block*) ; 
 scalar_t__ SB_FREE_BLOCKS (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ is_block_in_journal (struct super_block*,unsigned int,int,int*) ; 
 int /*<<< orphan*/  journal_mark_dirty (struct reiserfs_transaction_handle*,struct buffer_head*) ; 
 int reiserfs_bmap_count (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_clear_le_bit (int,scalar_t__) ; 
 int /*<<< orphan*/  reiserfs_error (struct super_block*,char*,char*,unsigned int) ; 
 int reiserfs_find_next_zero_le_bit (unsigned long*,int,int) ; 
 int /*<<< orphan*/  reiserfs_prepare_for_journal (struct super_block*,struct buffer_head*,int) ; 
 struct buffer_head* reiserfs_read_bitmap_block (struct super_block*,unsigned int) ; 
 int /*<<< orphan*/  reiserfs_restore_prepared_buffer (struct super_block*,struct buffer_head*) ; 
 scalar_t__ reiserfs_test_and_set_le_bit (int,scalar_t__) ; 
 scalar_t__ reiserfs_test_le_bit (int,scalar_t__) ; 
 TYPE_1__ scan_bitmap ; 

__attribute__((used)) static int scan_bitmap_block(struct reiserfs_transaction_handle *th,
			     unsigned int bmap_n, int *beg, int boundary,
			     int min, int max, int unfm)
{
	struct super_block *s = th->t_super;
	struct reiserfs_bitmap_info *bi = &SB_AP_BITMAP(s)[bmap_n];
	struct buffer_head *bh;
	int end, next;
	int org = *beg;

	BUG_ON(!th->t_trans_id);
	RFALSE(bmap_n >= reiserfs_bmap_count(s), "Bitmap %u is out of "
	       "range (0..%u)", bmap_n, reiserfs_bmap_count(s) - 1);
	PROC_INFO_INC(s, scan_bitmap.bmap);

	if (!bi) {
		reiserfs_error(s, "jdm-4055", "NULL bitmap info pointer "
			       "for bitmap %d", bmap_n);
		return 0;
	}

	bh = reiserfs_read_bitmap_block(s, bmap_n);
	if (bh == NULL)
		return 0;

	while (1) {
cont:
		if (bi->free_count < min) {
			brelse(bh);
			return 0;	/* No free blocks in this bitmap */
		}

		/* search for a first zero bit -- beginning of a window */
		*beg = reiserfs_find_next_zero_le_bit
		    ((unsigned long *)(bh->b_data), boundary, *beg);

		/*
		 * search for a zero bit fails or the rest of bitmap block
		 * cannot contain a zero window of minimum size
		 */
		if (*beg + min > boundary) {
			brelse(bh);
			return 0;
		}

		if (unfm && is_block_in_journal(s, bmap_n, *beg, beg))
			continue;
		/* first zero bit found; we check next bits */
		for (end = *beg + 1;; end++) {
			if (end >= *beg + max || end >= boundary
			    || reiserfs_test_le_bit(end, bh->b_data)) {
				next = end;
				break;
			}

			/*
			 * finding the other end of zero bit window requires
			 * looking into journal structures (in case of
			 * searching for free blocks for unformatted nodes)
			 */
			if (unfm && is_block_in_journal(s, bmap_n, end, &next))
				break;
		}

		/*
		 * now (*beg) points to beginning of zero bits window,
		 * (end) points to one bit after the window end
		 */

		/* found window of proper size */
		if (end - *beg >= min) {
			int i;
			reiserfs_prepare_for_journal(s, bh, 1);
			/*
			 * try to set all blocks used checking are
			 * they still free
			 */
			for (i = *beg; i < end; i++) {
				/* Don't check in journal again. */
				if (reiserfs_test_and_set_le_bit
				    (i, bh->b_data)) {
					/*
					 * bit was set by another process while
					 * we slept in prepare_for_journal()
					 */
					PROC_INFO_INC(s, scan_bitmap.stolen);

					/*
					 * we can continue with smaller set
					 * of allocated blocks, if length of
					 * this set is more or equal to `min'
					 */
					if (i >= *beg + min) {
						end = i;
						break;
					}

					/*
					 * otherwise we clear all bit
					 * were set ...
					 */
					while (--i >= *beg)
						reiserfs_clear_le_bit
						    (i, bh->b_data);
					reiserfs_restore_prepared_buffer(s, bh);
					*beg = org;

					/*
					 * Search again in current block
					 * from beginning
					 */
					goto cont;
				}
			}
			bi->free_count -= (end - *beg);
			journal_mark_dirty(th, bh);
			brelse(bh);

			/* free block count calculation */
			reiserfs_prepare_for_journal(s, SB_BUFFER_WITH_SB(s),
						     1);
			PUT_SB_FREE_BLOCKS(s, SB_FREE_BLOCKS(s) - (end - *beg));
			journal_mark_dirty(th, SB_BUFFER_WITH_SB(s));

			return end - (*beg);
		} else {
			*beg = next;
		}
	}
}