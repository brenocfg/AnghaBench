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
struct TYPE_2__ {struct list_head* next; } ;
struct reiserfs_journal_list {unsigned int j_trans_id; scalar_t__ j_len; int j_state; TYPE_1__ j_list; int /*<<< orphan*/  j_commit_left; } ;
struct list_head {int dummy; } ;
struct reiserfs_journal {int /*<<< orphan*/  j_flush_mutex; struct list_head j_journal_list; } ;
struct buffer_chunk {scalar_t__ nr; } ;

/* Variables and functions */
 struct reiserfs_journal_list* JOURNAL_LIST_ENTRY (struct list_head*) ; 
 int LIST_DIRTY ; 
 int LIST_TOUCHED ; 
 struct reiserfs_journal* SB_JOURNAL (struct super_block*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_from_work_list (struct super_block*,struct reiserfs_journal_list*) ; 
 int /*<<< orphan*/  journal_list_still_alive (struct super_block*,unsigned int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reiserfs_mutex_lock_safe (int /*<<< orphan*/ *,struct super_block*) ; 
 int /*<<< orphan*/  write_chunk (struct buffer_chunk*) ; 
 int write_one_transaction (struct super_block*,struct reiserfs_journal_list*,struct buffer_chunk*) ; 

__attribute__((used)) static int kupdate_transactions(struct super_block *s,
				struct reiserfs_journal_list *jl,
				struct reiserfs_journal_list **next_jl,
				unsigned int *next_trans_id,
				int num_blocks, int num_trans)
{
	int ret = 0;
	int written = 0;
	int transactions_flushed = 0;
	unsigned int orig_trans_id = jl->j_trans_id;
	struct buffer_chunk chunk;
	struct list_head *entry;
	struct reiserfs_journal *journal = SB_JOURNAL(s);
	chunk.nr = 0;

	reiserfs_mutex_lock_safe(&journal->j_flush_mutex, s);
	if (!journal_list_still_alive(s, orig_trans_id)) {
		goto done;
	}

	/*
	 * we've got j_flush_mutex held, nobody is going to delete any
	 * of these lists out from underneath us
	 */
	while ((num_trans && transactions_flushed < num_trans) ||
	       (!num_trans && written < num_blocks)) {

		if (jl->j_len == 0 || (jl->j_state & LIST_TOUCHED) ||
		    atomic_read(&jl->j_commit_left)
		    || !(jl->j_state & LIST_DIRTY)) {
			del_from_work_list(s, jl);
			break;
		}
		ret = write_one_transaction(s, jl, &chunk);

		if (ret < 0)
			goto done;
		transactions_flushed++;
		written += ret;
		entry = jl->j_list.next;

		/* did we wrap? */
		if (entry == &journal->j_journal_list) {
			break;
		}
		jl = JOURNAL_LIST_ENTRY(entry);

		/* don't bother with older transactions */
		if (jl->j_trans_id <= orig_trans_id)
			break;
	}
	if (chunk.nr) {
		write_chunk(&chunk);
	}

done:
	mutex_unlock(&journal->j_flush_mutex);
	return ret;
}