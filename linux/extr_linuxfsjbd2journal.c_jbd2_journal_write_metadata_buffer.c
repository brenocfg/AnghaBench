#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* t_journal; } ;
typedef  TYPE_1__ transaction_t ;
struct page {int dummy; } ;
struct journal_head {char* b_frozen_data; int /*<<< orphan*/  b_triggers; int /*<<< orphan*/  b_frozen_triggers; } ;
struct buffer_head {char* b_data; struct buffer_head* b_private; int /*<<< orphan*/  b_blocknr; int /*<<< orphan*/  b_bdev; int /*<<< orphan*/  b_size; struct page* b_page; int /*<<< orphan*/  b_count; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_6__ {int /*<<< orphan*/  j_list_lock; int /*<<< orphan*/  j_dev; } ;
typedef  TYPE_2__ journal_t ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  BJ_Shadow ; 
 int ENOMEM ; 
 int GFP_NOFS ; 
 int /*<<< orphan*/  JBD2_MAGIC_NUMBER ; 
 int /*<<< orphan*/  JBUFFER_TRACE (struct journal_head*,char*) ; 
 int /*<<< orphan*/  J_ASSERT_BH (struct buffer_head*,int /*<<< orphan*/ ) ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  __jbd2_journal_file_buffer (struct journal_head*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct buffer_head* alloc_buffer_head (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_jbddirty (struct buffer_head*) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 char* jbd2_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jbd2_buffer_frozen_trigger (struct journal_head*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd2_free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd_lock_bh_state (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_unlock_bh_state (struct buffer_head*) ; 
 struct buffer_head* jh2bh (struct journal_head*) ; 
 char* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 unsigned int offset_in_page (char*) ; 
 int /*<<< orphan*/  set_bh_page (struct buffer_head*,struct page*,unsigned int) ; 
 int /*<<< orphan*/  set_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_shadow (struct buffer_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct page* virt_to_page (char*) ; 

int jbd2_journal_write_metadata_buffer(transaction_t *transaction,
				  struct journal_head  *jh_in,
				  struct buffer_head **bh_out,
				  sector_t blocknr)
{
	int need_copy_out = 0;
	int done_copy_out = 0;
	int do_escape = 0;
	char *mapped_data;
	struct buffer_head *new_bh;
	struct page *new_page;
	unsigned int new_offset;
	struct buffer_head *bh_in = jh2bh(jh_in);
	journal_t *journal = transaction->t_journal;

	/*
	 * The buffer really shouldn't be locked: only the current committing
	 * transaction is allowed to write it, so nobody else is allowed
	 * to do any IO.
	 *
	 * akpm: except if we're journalling data, and write() output is
	 * also part of a shared mapping, and another thread has
	 * decided to launch a writepage() against this buffer.
	 */
	J_ASSERT_BH(bh_in, buffer_jbddirty(bh_in));

	new_bh = alloc_buffer_head(GFP_NOFS|__GFP_NOFAIL);

	/* keep subsequent assertions sane */
	atomic_set(&new_bh->b_count, 1);

	jbd_lock_bh_state(bh_in);
repeat:
	/*
	 * If a new transaction has already done a buffer copy-out, then
	 * we use that version of the data for the commit.
	 */
	if (jh_in->b_frozen_data) {
		done_copy_out = 1;
		new_page = virt_to_page(jh_in->b_frozen_data);
		new_offset = offset_in_page(jh_in->b_frozen_data);
	} else {
		new_page = jh2bh(jh_in)->b_page;
		new_offset = offset_in_page(jh2bh(jh_in)->b_data);
	}

	mapped_data = kmap_atomic(new_page);
	/*
	 * Fire data frozen trigger if data already wasn't frozen.  Do this
	 * before checking for escaping, as the trigger may modify the magic
	 * offset.  If a copy-out happens afterwards, it will have the correct
	 * data in the buffer.
	 */
	if (!done_copy_out)
		jbd2_buffer_frozen_trigger(jh_in, mapped_data + new_offset,
					   jh_in->b_triggers);

	/*
	 * Check for escaping
	 */
	if (*((__be32 *)(mapped_data + new_offset)) ==
				cpu_to_be32(JBD2_MAGIC_NUMBER)) {
		need_copy_out = 1;
		do_escape = 1;
	}
	kunmap_atomic(mapped_data);

	/*
	 * Do we need to do a data copy?
	 */
	if (need_copy_out && !done_copy_out) {
		char *tmp;

		jbd_unlock_bh_state(bh_in);
		tmp = jbd2_alloc(bh_in->b_size, GFP_NOFS);
		if (!tmp) {
			brelse(new_bh);
			return -ENOMEM;
		}
		jbd_lock_bh_state(bh_in);
		if (jh_in->b_frozen_data) {
			jbd2_free(tmp, bh_in->b_size);
			goto repeat;
		}

		jh_in->b_frozen_data = tmp;
		mapped_data = kmap_atomic(new_page);
		memcpy(tmp, mapped_data + new_offset, bh_in->b_size);
		kunmap_atomic(mapped_data);

		new_page = virt_to_page(tmp);
		new_offset = offset_in_page(tmp);
		done_copy_out = 1;

		/*
		 * This isn't strictly necessary, as we're using frozen
		 * data for the escaping, but it keeps consistency with
		 * b_frozen_data usage.
		 */
		jh_in->b_frozen_triggers = jh_in->b_triggers;
	}

	/*
	 * Did we need to do an escaping?  Now we've done all the
	 * copying, we can finally do so.
	 */
	if (do_escape) {
		mapped_data = kmap_atomic(new_page);
		*((unsigned int *)(mapped_data + new_offset)) = 0;
		kunmap_atomic(mapped_data);
	}

	set_bh_page(new_bh, new_page, new_offset);
	new_bh->b_size = bh_in->b_size;
	new_bh->b_bdev = journal->j_dev;
	new_bh->b_blocknr = blocknr;
	new_bh->b_private = bh_in;
	set_buffer_mapped(new_bh);
	set_buffer_dirty(new_bh);

	*bh_out = new_bh;

	/*
	 * The to-be-written buffer needs to get moved to the io queue,
	 * and the original buffer whose contents we are shadowing or
	 * copying is moved to the transaction's shadow queue.
	 */
	JBUFFER_TRACE(jh_in, "file as BJ_Shadow");
	spin_lock(&journal->j_list_lock);
	__jbd2_journal_file_buffer(jh_in, transaction, BJ_Shadow);
	spin_unlock(&journal->j_list_lock);
	set_buffer_shadow(bh_in);
	jbd_unlock_bh_state(bh_in);

	return do_escape | (done_copy_out << 1);
}