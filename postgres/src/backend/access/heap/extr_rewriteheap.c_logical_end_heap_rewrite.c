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
struct TYPE_6__ {int /*<<< orphan*/  vfd; int /*<<< orphan*/  path; } ;
struct TYPE_5__ {scalar_t__ rs_num_rewrite_mappings; int /*<<< orphan*/  rs_logical_mappings; int /*<<< orphan*/  rs_logical_rewrite; } ;
typedef  TYPE_1__* RewriteState ;
typedef  TYPE_2__ RewriteMappingFile ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ ) ; 
 scalar_t__ FileSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAIT_EVENT_LOGICAL_REWRITE_SYNC ; 
 int /*<<< orphan*/  data_sync_elevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logical_heap_rewrite_flush_mappings (TYPE_1__*) ; 

__attribute__((used)) static void
logical_end_heap_rewrite(RewriteState state)
{
	HASH_SEQ_STATUS seq_status;
	RewriteMappingFile *src;

	/* done, no logical rewrite in progress */
	if (!state->rs_logical_rewrite)
		return;

	/* writeout remaining in-memory entries */
	if (state->rs_num_rewrite_mappings > 0)
		logical_heap_rewrite_flush_mappings(state);

	/* Iterate over all mappings we have written and fsync the files. */
	hash_seq_init(&seq_status, state->rs_logical_mappings);
	while ((src = (RewriteMappingFile *) hash_seq_search(&seq_status)) != NULL)
	{
		if (FileSync(src->vfd, WAIT_EVENT_LOGICAL_REWRITE_SYNC) != 0)
			ereport(data_sync_elevel(ERROR),
					(errcode_for_file_access(),
					 errmsg("could not fsync file \"%s\": %m", src->path)));
		FileClose(src->vfd);
	}
	/* memory context cleanup will deal with the rest */
}