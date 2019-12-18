#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t handler; } ;
struct TYPE_6__ {scalar_t__ (* sync_unlinkfiletag ) (TYPE_3__*,char*) ;} ;
struct TYPE_5__ {scalar_t__ cycle_ctr; TYPE_3__ tag; } ;
typedef  TYPE_1__ PendingUnlinkEntry ;

/* Variables and functions */
 int /*<<< orphan*/  AbsorbSyncRequests () ; 
 scalar_t__ ENOENT ; 
 int MAXPGPATH ; 
 scalar_t__ NIL ; 
 int UNLINKS_PER_ABSORB ; 
 int /*<<< orphan*/  WARNING ; 
 scalar_t__ checkpoint_cycle_ctr ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 scalar_t__ errno ; 
 scalar_t__ linitial (scalar_t__) ; 
 scalar_t__ list_delete_first (scalar_t__) ; 
 scalar_t__ pendingUnlinks ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 scalar_t__ stub1 (TYPE_3__*,char*) ; 
 TYPE_2__* syncsw ; 

void
SyncPostCheckpoint(void)
{
	int			absorb_counter;

	absorb_counter = UNLINKS_PER_ABSORB;
	while (pendingUnlinks != NIL)
	{
		PendingUnlinkEntry *entry = (PendingUnlinkEntry *) linitial(pendingUnlinks);
		char		path[MAXPGPATH];

		/*
		 * New entries are appended to the end, so if the entry is new we've
		 * reached the end of old entries.
		 *
		 * Note: if just the right number of consecutive checkpoints fail, we
		 * could be fooled here by cycle_ctr wraparound.  However, the only
		 * consequence is that we'd delay unlinking for one more checkpoint,
		 * which is perfectly tolerable.
		 */
		if (entry->cycle_ctr == checkpoint_cycle_ctr)
			break;

		/* Unlink the file */
		if (syncsw[entry->tag.handler].sync_unlinkfiletag(&entry->tag,
														  path) < 0)
		{
			/*
			 * There's a race condition, when the database is dropped at the
			 * same time that we process the pending unlink requests. If the
			 * DROP DATABASE deletes the file before we do, we will get ENOENT
			 * here. rmtree() also has to ignore ENOENT errors, to deal with
			 * the possibility that we delete the file first.
			 */
			if (errno != ENOENT)
				ereport(WARNING,
						(errcode_for_file_access(),
						 errmsg("could not remove file \"%s\": %m", path)));
		}

		/* And remove the list entry */
		pendingUnlinks = list_delete_first(pendingUnlinks);
		pfree(entry);

		/*
		 * As in ProcessSyncRequests, we don't want to stop absorbing fsync
		 * requests for along time when there are many deletions to be done.
		 * We can safely call AbsorbSyncRequests() at this point in the loop
		 * (note it might try to delete list entries).
		 */
		if (--absorb_counter <= 0)
		{
			AbsorbSyncRequests();
			absorb_counter = UNLINKS_PER_ABSORB;
		}
	}
}