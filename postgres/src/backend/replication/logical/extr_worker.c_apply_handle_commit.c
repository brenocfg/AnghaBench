#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ commit_lsn; int /*<<< orphan*/  end_lsn; int /*<<< orphan*/  committime; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ LogicalRepCommitData ;

/* Variables and functions */
 int /*<<< orphan*/  AcceptInvalidationMessages () ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 scalar_t__ IsTransactionState () ; 
 int /*<<< orphan*/  STATE_IDLE ; 
 int /*<<< orphan*/  am_tablesync_worker () ; 
 int in_remote_transaction ; 
 int /*<<< orphan*/  logicalrep_read_commit (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  maybe_reread_subscription () ; 
 int /*<<< orphan*/  pgstat_report_activity (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgstat_report_stat (int) ; 
 int /*<<< orphan*/  process_syncing_tables (int /*<<< orphan*/ ) ; 
 scalar_t__ remote_final_lsn ; 
 int /*<<< orphan*/  replorigin_session_origin_lsn ; 
 int /*<<< orphan*/  replorigin_session_origin_timestamp ; 
 int /*<<< orphan*/  store_flush_position (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
apply_handle_commit(StringInfo s)
{
	LogicalRepCommitData commit_data;

	logicalrep_read_commit(s, &commit_data);

	Assert(commit_data.commit_lsn == remote_final_lsn);

	/* The synchronization worker runs in single transaction. */
	if (IsTransactionState() && !am_tablesync_worker())
	{
		/*
		 * Update origin state so we can restart streaming from correct
		 * position in case of crash.
		 */
		replorigin_session_origin_lsn = commit_data.end_lsn;
		replorigin_session_origin_timestamp = commit_data.committime;

		CommitTransactionCommand();
		pgstat_report_stat(false);

		store_flush_position(commit_data.end_lsn);
	}
	else
	{
		/* Process any invalidation messages that might have accumulated. */
		AcceptInvalidationMessages();
		maybe_reread_subscription();
	}

	in_remote_transaction = false;

	/* Process any tables that are being synchronized in parallel. */
	process_syncing_tables(commit_data.end_lsn);

	pgstat_report_activity(STATE_IDLE, NULL);
}