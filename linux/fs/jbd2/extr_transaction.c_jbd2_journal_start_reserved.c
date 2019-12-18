#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__* j_fs_dev; } ;
typedef  TYPE_3__ journal_t ;
struct TYPE_15__ {unsigned int h_type; unsigned int h_line_no; int /*<<< orphan*/  h_buffer_credits; TYPE_2__* h_transaction; TYPE_3__* h_journal; int /*<<< orphan*/  h_reserved; } ;
typedef  TYPE_4__ handle_t ;
struct TYPE_13__ {int /*<<< orphan*/  t_tid; } ;
struct TYPE_12__ {int /*<<< orphan*/  bd_dev; } ;
struct TYPE_11__ {int journal_info; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ WARN_ON (int) ; 
 TYPE_10__* current ; 
 int /*<<< orphan*/  jbd2_journal_free_reserved (TYPE_4__*) ; 
 int /*<<< orphan*/  jbd2_journal_stop (TYPE_4__*) ; 
 int start_this_handle (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_jbd2_handle_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

int jbd2_journal_start_reserved(handle_t *handle, unsigned int type,
				unsigned int line_no)
{
	journal_t *journal = handle->h_journal;
	int ret = -EIO;

	if (WARN_ON(!handle->h_reserved)) {
		/* Someone passed in normal handle? Just stop it. */
		jbd2_journal_stop(handle);
		return ret;
	}
	/*
	 * Usefulness of mixing of reserved and unreserved handles is
	 * questionable. So far nobody seems to need it so just error out.
	 */
	if (WARN_ON(current->journal_info)) {
		jbd2_journal_free_reserved(handle);
		return ret;
	}

	handle->h_journal = NULL;
	/*
	 * GFP_NOFS is here because callers are likely from writeback or
	 * similarly constrained call sites
	 */
	ret = start_this_handle(journal, handle, GFP_NOFS);
	if (ret < 0) {
		handle->h_journal = journal;
		jbd2_journal_free_reserved(handle);
		return ret;
	}
	handle->h_type = type;
	handle->h_line_no = line_no;
	trace_jbd2_handle_start(journal->j_fs_dev->bd_dev,
				handle->h_transaction->t_tid, type,
				line_no, handle->h_buffer_credits);
	return 0;
}