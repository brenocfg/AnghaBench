#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_7__ {unsigned int h_type; unsigned int h_line_no; int /*<<< orphan*/ * h_journal; int /*<<< orphan*/  h_reserved; } ;
typedef  TYPE_1__ handle_t ;
struct TYPE_8__ {int journal_info; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ WARN_ON (int) ; 
 TYPE_6__* current ; 
 int /*<<< orphan*/  jbd2_journal_free_reserved (TYPE_1__*) ; 
 int /*<<< orphan*/  jbd2_journal_stop (TYPE_1__*) ; 
 int start_this_handle (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

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
	return 0;
}