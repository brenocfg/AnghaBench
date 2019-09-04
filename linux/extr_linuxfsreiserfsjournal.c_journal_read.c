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
typedef  scalar_t__ time64_t ;
struct super_block {int /*<<< orphan*/  s_bdev; int /*<<< orphan*/  s_blocksize; } ;
struct reiserfs_journal_header {int /*<<< orphan*/  j_mount_id; int /*<<< orphan*/  j_last_flush_trans_id; int /*<<< orphan*/  j_first_unflushed_offset; } ;
struct reiserfs_journal_desc {int dummy; } ;
struct reiserfs_journal {unsigned long j_start; int j_trans_id; int j_last_flush_trans_id; int j_mount_id; int j_first_unflushed_offset; int /*<<< orphan*/  j_dev_bd; TYPE_1__* j_header_bh; } ;
struct buffer_head {unsigned long b_blocknr; scalar_t__ b_data; } ;
struct TYPE_2__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  REISERFS_DEBUG_CODE ; 
 struct reiserfs_journal* SB_JOURNAL (struct super_block*) ; 
 unsigned long SB_ONDISK_JOURNAL_1st_BLOCK (struct super_block*) ; 
 unsigned long SB_ONDISK_JOURNAL_SIZE (struct super_block*) ; 
 scalar_t__ _update_journal_header_block (struct super_block*,int,int) ; 
 int /*<<< orphan*/  bdev_read_only (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 unsigned long get_desc_mount_id (struct reiserfs_journal_desc*) ; 
 unsigned int get_desc_trans_id (struct reiserfs_journal_desc*) ; 
 scalar_t__ get_desc_trans_len (struct reiserfs_journal_desc*) ; 
 void* journal_bread (struct super_block*,int) ; 
 int journal_read_transaction (struct super_block*,unsigned long,unsigned long,unsigned int,unsigned long) ; 
 int journal_transaction_is_valid (struct super_block*,struct buffer_head*,unsigned int*,unsigned long*) ; 
 scalar_t__ ktime_get_seconds () ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct buffer_head* reiserfs_breada (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  reiserfs_debug (struct super_block*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  reiserfs_info (struct super_block*,char*,int,...) ; 
 int /*<<< orphan*/  reiserfs_write_lock (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (struct super_block*) ; 

__attribute__((used)) static int journal_read(struct super_block *sb)
{
	struct reiserfs_journal *journal = SB_JOURNAL(sb);
	struct reiserfs_journal_desc *desc;
	unsigned int oldest_trans_id = 0;
	unsigned int oldest_invalid_trans_id = 0;
	time64_t start;
	unsigned long oldest_start = 0;
	unsigned long cur_dblock = 0;
	unsigned long newest_mount_id = 9;
	struct buffer_head *d_bh;
	struct reiserfs_journal_header *jh;
	int valid_journal_header = 0;
	int replay_count = 0;
	int continue_replay = 1;
	int ret;

	cur_dblock = SB_ONDISK_JOURNAL_1st_BLOCK(sb);
	reiserfs_info(sb, "checking transaction log (%pg)\n",
		      journal->j_dev_bd);
	start = ktime_get_seconds();

	/*
	 * step 1, read in the journal header block.  Check the transaction
	 * it says is the first unflushed, and if that transaction is not
	 * valid, replay is done
	 */
	journal->j_header_bh = journal_bread(sb,
					     SB_ONDISK_JOURNAL_1st_BLOCK(sb)
					     + SB_ONDISK_JOURNAL_SIZE(sb));
	if (!journal->j_header_bh) {
		return 1;
	}
	jh = (struct reiserfs_journal_header *)(journal->j_header_bh->b_data);
	if (le32_to_cpu(jh->j_first_unflushed_offset) <
	    SB_ONDISK_JOURNAL_SIZE(sb)
	    && le32_to_cpu(jh->j_last_flush_trans_id) > 0) {
		oldest_start =
		    SB_ONDISK_JOURNAL_1st_BLOCK(sb) +
		    le32_to_cpu(jh->j_first_unflushed_offset);
		oldest_trans_id = le32_to_cpu(jh->j_last_flush_trans_id) + 1;
		newest_mount_id = le32_to_cpu(jh->j_mount_id);
		reiserfs_debug(sb, REISERFS_DEBUG_CODE,
			       "journal-1153: found in "
			       "header: first_unflushed_offset %d, last_flushed_trans_id "
			       "%lu", le32_to_cpu(jh->j_first_unflushed_offset),
			       le32_to_cpu(jh->j_last_flush_trans_id));
		valid_journal_header = 1;

		/*
		 * now, we try to read the first unflushed offset.  If it
		 * is not valid, there is nothing more we can do, and it
		 * makes no sense to read through the whole log.
		 */
		d_bh =
		    journal_bread(sb,
				  SB_ONDISK_JOURNAL_1st_BLOCK(sb) +
				  le32_to_cpu(jh->j_first_unflushed_offset));
		ret = journal_transaction_is_valid(sb, d_bh, NULL, NULL);
		if (!ret) {
			continue_replay = 0;
		}
		brelse(d_bh);
		goto start_log_replay;
	}

	/*
	 * ok, there are transactions that need to be replayed.  start
	 * with the first log block, find all the valid transactions, and
	 * pick out the oldest.
	 */
	while (continue_replay
	       && cur_dblock <
	       (SB_ONDISK_JOURNAL_1st_BLOCK(sb) +
		SB_ONDISK_JOURNAL_SIZE(sb))) {
		/*
		 * Note that it is required for blocksize of primary fs
		 * device and journal device to be the same
		 */
		d_bh =
		    reiserfs_breada(journal->j_dev_bd, cur_dblock,
				    sb->s_blocksize,
				    SB_ONDISK_JOURNAL_1st_BLOCK(sb) +
				    SB_ONDISK_JOURNAL_SIZE(sb));
		ret =
		    journal_transaction_is_valid(sb, d_bh,
						 &oldest_invalid_trans_id,
						 &newest_mount_id);
		if (ret == 1) {
			desc = (struct reiserfs_journal_desc *)d_bh->b_data;
			if (oldest_start == 0) {	/* init all oldest_ values */
				oldest_trans_id = get_desc_trans_id(desc);
				oldest_start = d_bh->b_blocknr;
				newest_mount_id = get_desc_mount_id(desc);
				reiserfs_debug(sb, REISERFS_DEBUG_CODE,
					       "journal-1179: Setting "
					       "oldest_start to offset %llu, trans_id %lu",
					       oldest_start -
					       SB_ONDISK_JOURNAL_1st_BLOCK
					       (sb), oldest_trans_id);
			} else if (oldest_trans_id > get_desc_trans_id(desc)) {
				/* one we just read was older */
				oldest_trans_id = get_desc_trans_id(desc);
				oldest_start = d_bh->b_blocknr;
				reiserfs_debug(sb, REISERFS_DEBUG_CODE,
					       "journal-1180: Resetting "
					       "oldest_start to offset %lu, trans_id %lu",
					       oldest_start -
					       SB_ONDISK_JOURNAL_1st_BLOCK
					       (sb), oldest_trans_id);
			}
			if (newest_mount_id < get_desc_mount_id(desc)) {
				newest_mount_id = get_desc_mount_id(desc);
				reiserfs_debug(sb, REISERFS_DEBUG_CODE,
					       "journal-1299: Setting "
					       "newest_mount_id to %d",
					       get_desc_mount_id(desc));
			}
			cur_dblock += get_desc_trans_len(desc) + 2;
		} else {
			cur_dblock++;
		}
		brelse(d_bh);
	}

start_log_replay:
	cur_dblock = oldest_start;
	if (oldest_trans_id) {
		reiserfs_debug(sb, REISERFS_DEBUG_CODE,
			       "journal-1206: Starting replay "
			       "from offset %llu, trans_id %lu",
			       cur_dblock - SB_ONDISK_JOURNAL_1st_BLOCK(sb),
			       oldest_trans_id);

	}
	replay_count = 0;
	while (continue_replay && oldest_trans_id > 0) {
		ret =
		    journal_read_transaction(sb, cur_dblock, oldest_start,
					     oldest_trans_id, newest_mount_id);
		if (ret < 0) {
			return ret;
		} else if (ret != 0) {
			break;
		}
		cur_dblock =
		    SB_ONDISK_JOURNAL_1st_BLOCK(sb) + journal->j_start;
		replay_count++;
		if (cur_dblock == oldest_start)
			break;
	}

	if (oldest_trans_id == 0) {
		reiserfs_debug(sb, REISERFS_DEBUG_CODE,
			       "journal-1225: No valid " "transactions found");
	}
	/*
	 * j_start does not get set correctly if we don't replay any
	 * transactions.  if we had a valid journal_header, set j_start
	 * to the first unflushed transaction value, copy the trans_id
	 * from the header
	 */
	if (valid_journal_header && replay_count == 0) {
		journal->j_start = le32_to_cpu(jh->j_first_unflushed_offset);
		journal->j_trans_id =
		    le32_to_cpu(jh->j_last_flush_trans_id) + 1;
		/* check for trans_id overflow */
		if (journal->j_trans_id == 0)
			journal->j_trans_id = 10;
		journal->j_last_flush_trans_id =
		    le32_to_cpu(jh->j_last_flush_trans_id);
		journal->j_mount_id = le32_to_cpu(jh->j_mount_id) + 1;
	} else {
		journal->j_mount_id = newest_mount_id + 1;
	}
	reiserfs_debug(sb, REISERFS_DEBUG_CODE, "journal-1299: Setting "
		       "newest_mount_id to %lu", journal->j_mount_id);
	journal->j_first_unflushed_offset = journal->j_start;
	if (replay_count > 0) {
		reiserfs_info(sb,
			      "replayed %d transactions in %lu seconds\n",
			      replay_count, ktime_get_seconds() - start);
	}
	/* needed to satisfy the locking in _update_journal_header_block */
	reiserfs_write_lock(sb);
	if (!bdev_read_only(sb->s_bdev) &&
	    _update_journal_header_block(sb, journal->j_start,
					 journal->j_last_flush_trans_id)) {
		reiserfs_write_unlock(sb);
		/*
		 * replay failed, caller must call free_journal_ram and abort
		 * the mount
		 */
		return -1;
	}
	reiserfs_write_unlock(sb);
	return 0;
}