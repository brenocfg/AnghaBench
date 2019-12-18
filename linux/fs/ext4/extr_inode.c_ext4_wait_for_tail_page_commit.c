#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tid_t ;
struct page {int dummy; } ;
struct inode {int i_size; int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_sb; } ;
struct TYPE_6__ {int /*<<< orphan*/  j_state_lock; TYPE_1__* j_committing_transaction; } ;
typedef  TYPE_2__ journal_t ;
struct TYPE_7__ {TYPE_2__* s_journal; } ;
struct TYPE_5__ {scalar_t__ t_tid; } ;

/* Variables and functions */
 int EBUSY ; 
 TYPE_4__* EXT4_SB (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int __ext4_journalled_invalidatepage (struct page*,unsigned int,int) ; 
 struct page* find_lock_page (int /*<<< orphan*/ ,int) ; 
 int i_blocksize (struct inode*) ; 
 int /*<<< orphan*/  jbd2_log_wait_commit (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static void ext4_wait_for_tail_page_commit(struct inode *inode)
{
	struct page *page;
	unsigned offset;
	journal_t *journal = EXT4_SB(inode->i_sb)->s_journal;
	tid_t commit_tid = 0;
	int ret;

	offset = inode->i_size & (PAGE_SIZE - 1);
	/*
	 * All buffers in the last page remain valid? Then there's nothing to
	 * do. We do the check mainly to optimize the common PAGE_SIZE ==
	 * blocksize case
	 */
	if (offset > PAGE_SIZE - i_blocksize(inode))
		return;
	while (1) {
		page = find_lock_page(inode->i_mapping,
				      inode->i_size >> PAGE_SHIFT);
		if (!page)
			return;
		ret = __ext4_journalled_invalidatepage(page, offset,
						PAGE_SIZE - offset);
		unlock_page(page);
		put_page(page);
		if (ret != -EBUSY)
			return;
		commit_tid = 0;
		read_lock(&journal->j_state_lock);
		if (journal->j_committing_transaction)
			commit_tid = journal->j_committing_transaction->t_tid;
		read_unlock(&journal->j_state_lock);
		if (commit_tid)
			jbd2_log_wait_commit(journal, commit_tid);
	}
}