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
struct reiserfs_journal_list {scalar_t__ j_len; struct reiserfs_journal_cnode* j_realblock; int /*<<< orphan*/  j_nonzerolen; int /*<<< orphan*/  j_state; } ;
struct reiserfs_journal_cnode {scalar_t__ blocknr; struct reiserfs_journal_cnode* next; struct buffer_head* bh; } ;
struct buffer_head {int dummy; } ;
struct buffer_chunk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  LIST_TOUCHED ; 
 int /*<<< orphan*/  add_to_chunk (struct buffer_chunk*,struct buffer_head*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_journal_dirty (struct buffer_head*) ; 
 scalar_t__ buffer_journal_prepared (struct buffer_head*) ; 
 scalar_t__ can_dirty (struct reiserfs_journal_cnode*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  del_from_work_list (struct super_block*,struct reiserfs_journal_list*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  write_chunk ; 

__attribute__((used)) static int write_one_transaction(struct super_block *s,
				 struct reiserfs_journal_list *jl,
				 struct buffer_chunk *chunk)
{
	struct reiserfs_journal_cnode *cn;
	int ret = 0;

	jl->j_state |= LIST_TOUCHED;
	del_from_work_list(s, jl);
	if (jl->j_len == 0 || atomic_read(&jl->j_nonzerolen) == 0) {
		return 0;
	}

	cn = jl->j_realblock;
	while (cn) {
		/*
		 * if the blocknr == 0, this has been cleared from the hash,
		 * skip it
		 */
		if (cn->blocknr == 0) {
			goto next;
		}
		if (cn->bh && can_dirty(cn) && buffer_dirty(cn->bh)) {
			struct buffer_head *tmp_bh;
			/*
			 * we can race against journal_mark_freed when we try
			 * to lock_buffer(cn->bh), so we have to inc the buffer
			 * count, and recheck things after locking
			 */
			tmp_bh = cn->bh;
			get_bh(tmp_bh);
			lock_buffer(tmp_bh);
			if (cn->bh && can_dirty(cn) && buffer_dirty(tmp_bh)) {
				if (!buffer_journal_dirty(tmp_bh) ||
				    buffer_journal_prepared(tmp_bh))
					BUG();
				add_to_chunk(chunk, tmp_bh, NULL, write_chunk);
				ret++;
			} else {
				/* note, cn->bh might be null now */
				unlock_buffer(tmp_bh);
			}
			put_bh(tmp_bh);
		}
next:
		cn = cn->next;
		cond_resched();
	}
	return ret;
}