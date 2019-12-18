#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct reiserfs_transaction_handle {int /*<<< orphan*/  t_trans_id; } ;
struct reiserfs_list_bitmap {int dummy; } ;
struct reiserfs_journal_cnode {scalar_t__ blocknr; struct reiserfs_journal_cnode* hnext; struct buffer_head* bh; TYPE_2__* jlist; int /*<<< orphan*/  state; struct super_block* sb; } ;
struct reiserfs_journal {int /*<<< orphan*/  j_list_hash_table; TYPE_1__* j_current_jl; int /*<<< orphan*/  j_hash_table; } ;
struct buffer_head {int /*<<< orphan*/  b_count; } ;
typedef  scalar_t__ b_blocknr_t ;
struct TYPE_4__ {int /*<<< orphan*/  j_nonzerolen; } ;
struct TYPE_3__ {struct reiserfs_list_bitmap* j_list_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FREED ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct reiserfs_journal* SB_JOURNAL (struct super_block*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ buffer_journal_new (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_journal_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_journal_new (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_journal_test (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_prepared_bits (struct buffer_head*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 struct reiserfs_journal_cnode* get_journal_hash_dev (struct super_block*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  reiserfs_clean_and_file_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  reiserfs_panic (struct super_block*,char*,char*) ; 
 int /*<<< orphan*/  reiserfs_warning (struct super_block*,char*,char*) ; 
 int /*<<< orphan*/  release_buffer_page (struct buffer_head*) ; 
 int remove_from_transaction (struct super_block*,scalar_t__,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit_in_list_bitmap (struct super_block*,scalar_t__,struct reiserfs_list_bitmap*) ; 

int journal_mark_freed(struct reiserfs_transaction_handle *th,
		       struct super_block *sb, b_blocknr_t blocknr)
{
	struct reiserfs_journal *journal = SB_JOURNAL(sb);
	struct reiserfs_journal_cnode *cn = NULL;
	struct buffer_head *bh = NULL;
	struct reiserfs_list_bitmap *jb = NULL;
	int cleaned = 0;
	BUG_ON(!th->t_trans_id);

	cn = get_journal_hash_dev(sb, journal->j_hash_table, blocknr);
	if (cn && cn->bh) {
		bh = cn->bh;
		get_bh(bh);
	}
	/* if it is journal new, we just remove it from this transaction */
	if (bh && buffer_journal_new(bh)) {
		clear_buffer_journal_new(bh);
		clear_prepared_bits(bh);
		reiserfs_clean_and_file_buffer(bh);
		cleaned = remove_from_transaction(sb, blocknr, cleaned);
	} else {
		/*
		 * set the bit for this block in the journal bitmap
		 * for this transaction
		 */
		jb = journal->j_current_jl->j_list_bitmap;
		if (!jb) {
			reiserfs_panic(sb, "journal-1702",
				       "journal_list_bitmap is NULL");
		}
		set_bit_in_list_bitmap(sb, blocknr, jb);

		/* Note, the entire while loop is not allowed to schedule.  */

		if (bh) {
			clear_prepared_bits(bh);
			reiserfs_clean_and_file_buffer(bh);
		}
		cleaned = remove_from_transaction(sb, blocknr, cleaned);

		/*
		 * find all older transactions with this block,
		 * make sure they don't try to write it out
		 */
		cn = get_journal_hash_dev(sb, journal->j_list_hash_table,
					  blocknr);
		while (cn) {
			if (sb == cn->sb && blocknr == cn->blocknr) {
				set_bit(BLOCK_FREED, &cn->state);
				if (cn->bh) {
					/*
					 * remove_from_transaction will brelse
					 * the buffer if it was in the current
					 * trans
					 */
					if (!cleaned) {
						clear_buffer_journal_dirty(cn->
									   bh);
						clear_buffer_dirty(cn->bh);
						clear_buffer_journal_test(cn->
									  bh);
						cleaned = 1;
						put_bh(cn->bh);
						if (atomic_read
						    (&cn->bh->b_count) < 0) {
							reiserfs_warning(sb,
								 "journal-2138",
								 "cn->bh->b_count < 0");
						}
					}
					/*
					 * since we are clearing the bh,
					 * we MUST dec nonzerolen
					 */
					if (cn->jlist) {
						atomic_dec(&cn->jlist->
							   j_nonzerolen);
					}
					cn->bh = NULL;
				}
			}
			cn = cn->hnext;
		}
	}

	if (bh)
		release_buffer_page(bh); /* get_hash grabs the buffer */
	return 0;
}