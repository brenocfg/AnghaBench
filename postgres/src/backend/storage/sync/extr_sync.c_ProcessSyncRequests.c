#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
typedef  int /*<<< orphan*/  instr_time ;
struct TYPE_9__ {int ckpt_sync_rels; scalar_t__ ckpt_agg_sync_time; scalar_t__ ckpt_longest_sync; } ;
struct TYPE_8__ {size_t handler; } ;
struct TYPE_7__ {scalar_t__ (* sync_syncfiletag ) (TYPE_3__*,char*) ;} ;
struct TYPE_6__ {scalar_t__ cycle_ctr; TYPE_3__ tag; int /*<<< orphan*/  canceled; } ;
typedef  TYPE_1__ PendingFsyncEntry ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;
typedef  scalar_t__ CycleCtr ;

/* Variables and functions */
 int /*<<< orphan*/  AbsorbSyncRequests () ; 
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_5__ CheckpointStats ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FILE_POSSIBLY_DELETED (int /*<<< orphan*/ ) ; 
 int FSYNCS_PER_ABSORB ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 scalar_t__ INSTR_TIME_GET_MICROSEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_SET_CURRENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_SUBTRACT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  data_sync_elevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  enableFsync ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * hash_search (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 
 scalar_t__ log_checkpoints ; 
 int /*<<< orphan*/  pendingOps ; 
 scalar_t__ stub1 (TYPE_3__*,char*) ; 
 scalar_t__ sync_cycle_ctr ; 
 TYPE_2__* syncsw ; 

void
ProcessSyncRequests(void)
{
	static bool sync_in_progress = false;

	HASH_SEQ_STATUS hstat;
	PendingFsyncEntry *entry;
	int			absorb_counter;

	/* Statistics on sync times */
	int			processed = 0;
	instr_time	sync_start,
				sync_end,
				sync_diff;
	uint64		elapsed;
	uint64		longest = 0;
	uint64		total_elapsed = 0;

	/*
	 * This is only called during checkpoints, and checkpoints should only
	 * occur in processes that have created a pendingOps.
	 */
	if (!pendingOps)
		elog(ERROR, "cannot sync without a pendingOps table");

	/*
	 * If we are in the checkpointer, the sync had better include all fsync
	 * requests that were queued by backends up to this point.  The tightest
	 * race condition that could occur is that a buffer that must be written
	 * and fsync'd for the checkpoint could have been dumped by a backend just
	 * before it was visited by BufferSync().  We know the backend will have
	 * queued an fsync request before clearing the buffer's dirtybit, so we
	 * are safe as long as we do an Absorb after completing BufferSync().
	 */
	AbsorbSyncRequests();

	/*
	 * To avoid excess fsync'ing (in the worst case, maybe a never-terminating
	 * checkpoint), we want to ignore fsync requests that are entered into the
	 * hashtable after this point --- they should be processed next time,
	 * instead.  We use sync_cycle_ctr to tell old entries apart from new
	 * ones: new ones will have cycle_ctr equal to the incremented value of
	 * sync_cycle_ctr.
	 *
	 * In normal circumstances, all entries present in the table at this point
	 * will have cycle_ctr exactly equal to the current (about to be old)
	 * value of sync_cycle_ctr.  However, if we fail partway through the
	 * fsync'ing loop, then older values of cycle_ctr might remain when we
	 * come back here to try again.  Repeated checkpoint failures would
	 * eventually wrap the counter around to the point where an old entry
	 * might appear new, causing us to skip it, possibly allowing a checkpoint
	 * to succeed that should not have.  To forestall wraparound, any time the
	 * previous ProcessSyncRequests() failed to complete, run through the
	 * table and forcibly set cycle_ctr = sync_cycle_ctr.
	 *
	 * Think not to merge this loop with the main loop, as the problem is
	 * exactly that that loop may fail before having visited all the entries.
	 * From a performance point of view it doesn't matter anyway, as this path
	 * will never be taken in a system that's functioning normally.
	 */
	if (sync_in_progress)
	{
		/* prior try failed, so update any stale cycle_ctr values */
		hash_seq_init(&hstat, pendingOps);
		while ((entry = (PendingFsyncEntry *) hash_seq_search(&hstat)) != NULL)
		{
			entry->cycle_ctr = sync_cycle_ctr;
		}
	}

	/* Advance counter so that new hashtable entries are distinguishable */
	sync_cycle_ctr++;

	/* Set flag to detect failure if we don't reach the end of the loop */
	sync_in_progress = true;

	/* Now scan the hashtable for fsync requests to process */
	absorb_counter = FSYNCS_PER_ABSORB;
	hash_seq_init(&hstat, pendingOps);
	while ((entry = (PendingFsyncEntry *) hash_seq_search(&hstat)) != NULL)
	{
		int			failures;

		/*
		 * If fsync is off then we don't have to bother opening the file at
		 * all.  (We delay checking until this point so that changing fsync on
		 * the fly behaves sensibly.)
		 */
		if (!enableFsync)
			continue;

		/*
		 * If the entry is new then don't process it this time; it is new.
		 * Note "continue" bypasses the hash-remove call at the bottom of the
		 * loop.
		 */
		if (entry->cycle_ctr == sync_cycle_ctr)
			continue;

		/* Else assert we haven't missed it */
		Assert((CycleCtr) (entry->cycle_ctr + 1) == sync_cycle_ctr);

		/*
		 * If in checkpointer, we want to absorb pending requests every so
		 * often to prevent overflow of the fsync request queue.  It is
		 * unspecified whether newly-added entries will be visited by
		 * hash_seq_search, but we don't care since we don't need to process
		 * them anyway.
		 */
		if (--absorb_counter <= 0)
		{
			AbsorbSyncRequests();
			absorb_counter = FSYNCS_PER_ABSORB;
		}

		/*
		 * The fsync table could contain requests to fsync segments that have
		 * been deleted (unlinked) by the time we get to them. Rather than
		 * just hoping an ENOENT (or EACCES on Windows) error can be ignored,
		 * what we do on error is absorb pending requests and then retry.
		 * Since mdunlink() queues a "cancel" message before actually
		 * unlinking, the fsync request is guaranteed to be marked canceled
		 * after the absorb if it really was this case. DROP DATABASE likewise
		 * has to tell us to forget fsync requests before it starts deletions.
		 */
		for (failures = 0; !entry->canceled; failures++)
		{
			char		path[MAXPGPATH];

			INSTR_TIME_SET_CURRENT(sync_start);
			if (syncsw[entry->tag.handler].sync_syncfiletag(&entry->tag,
															path) == 0)
			{
				/* Success; update statistics about sync timing */
				INSTR_TIME_SET_CURRENT(sync_end);
				sync_diff = sync_end;
				INSTR_TIME_SUBTRACT(sync_diff, sync_start);
				elapsed = INSTR_TIME_GET_MICROSEC(sync_diff);
				if (elapsed > longest)
					longest = elapsed;
				total_elapsed += elapsed;
				processed++;

				if (log_checkpoints)
					elog(DEBUG1, "checkpoint sync: number=%d file=%s time=%.3f msec",
						 processed,
						 path,
						 (double) elapsed / 1000);

				break;			/* out of retry loop */
			}

			/*
			 * It is possible that the relation has been dropped or truncated
			 * since the fsync request was entered. Therefore, allow ENOENT,
			 * but only if we didn't fail already on this file.
			 */
			if (!FILE_POSSIBLY_DELETED(errno) || failures > 0)
				ereport(data_sync_elevel(ERROR),
						(errcode_for_file_access(),
						 errmsg("could not fsync file \"%s\": %m",
								path)));
			else
				ereport(DEBUG1,
						(errcode_for_file_access(),
						 errmsg("could not fsync file \"%s\" but retrying: %m",
								path)));

			/*
			 * Absorb incoming requests and check to see if a cancel arrived
			 * for this relation fork.
			 */
			AbsorbSyncRequests();
			absorb_counter = FSYNCS_PER_ABSORB; /* might as well... */
		}						/* end retry loop */

		/* We are done with this entry, remove it */
		if (hash_search(pendingOps, &entry->tag, HASH_REMOVE, NULL) == NULL)
			elog(ERROR, "pendingOps corrupted");
	}							/* end loop over hashtable entries */

	/* Return sync performance metrics for report at checkpoint end */
	CheckpointStats.ckpt_sync_rels = processed;
	CheckpointStats.ckpt_longest_sync = longest;
	CheckpointStats.ckpt_agg_sync_time = total_elapsed;

	/* Flag successful completion of ProcessSyncRequests */
	sync_in_progress = false;
}