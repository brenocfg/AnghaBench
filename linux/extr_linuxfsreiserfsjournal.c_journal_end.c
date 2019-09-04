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
struct reiserfs_transaction_handle {int t_refcount; scalar_t__ t_trans_id; struct super_block* t_super; } ;
struct TYPE_2__ {struct reiserfs_transaction_handle* journal_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_1__* current ; 
 int do_journal_end (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct reiserfs_transaction_handle*,struct reiserfs_transaction_handle*,int) ; 
 int /*<<< orphan*/  reiserfs_warning (struct super_block*,char*,char*,int) ; 

int journal_end(struct reiserfs_transaction_handle *th)
{
	struct super_block *sb = th->t_super;
	if (!current->journal_info && th->t_refcount > 1)
		reiserfs_warning(sb, "REISER-NESTING",
				 "th NULL, refcount %d", th->t_refcount);

	if (!th->t_trans_id) {
		WARN_ON(1);
		return -EIO;
	}

	th->t_refcount--;
	if (th->t_refcount > 0) {
		struct reiserfs_transaction_handle *cur_th =
		    current->journal_info;

		/*
		 * we aren't allowed to close a nested transaction on a
		 * different filesystem from the one in the task struct
		 */
		BUG_ON(cur_th->t_super != th->t_super);

		if (th != cur_th) {
			memcpy(current->journal_info, th, sizeof(*th));
			th->t_trans_id = 0;
		}
		return 0;
	} else {
		return do_journal_end(th, 0);
	}
}