#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_3__ {scalar_t__ catalog_xmin; scalar_t__ restart_lsn; scalar_t__ confirmed_flush; } ;
struct TYPE_4__ {scalar_t__ candidate_xmin_lsn; scalar_t__ candidate_restart_valid; scalar_t__ candidate_catalog_xmin; scalar_t__ candidate_restart_lsn; scalar_t__ effective_catalog_xmin; int /*<<< orphan*/  mutex; TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DEBUG1 ; 
 scalar_t__ InvalidTransactionId ; 
 scalar_t__ InvalidXLogRecPtr ; 
 TYPE_2__* MyReplicationSlot ; 
 int /*<<< orphan*/  ReplicationSlotMarkDirty () ; 
 int /*<<< orphan*/  ReplicationSlotSave () ; 
 int /*<<< orphan*/  ReplicationSlotsComputeRequiredLSN () ; 
 int /*<<< orphan*/  ReplicationSlotsComputeRequiredXmin (int) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 scalar_t__ TransactionIdIsValid (scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,int) ; 

void
LogicalConfirmReceivedLocation(XLogRecPtr lsn)
{
	Assert(lsn != InvalidXLogRecPtr);

	/* Do an unlocked check for candidate_lsn first. */
	if (MyReplicationSlot->candidate_xmin_lsn != InvalidXLogRecPtr ||
		MyReplicationSlot->candidate_restart_valid != InvalidXLogRecPtr)
	{
		bool		updated_xmin = false;
		bool		updated_restart = false;

		SpinLockAcquire(&MyReplicationSlot->mutex);

		MyReplicationSlot->data.confirmed_flush = lsn;

		/* if we're past the location required for bumping xmin, do so */
		if (MyReplicationSlot->candidate_xmin_lsn != InvalidXLogRecPtr &&
			MyReplicationSlot->candidate_xmin_lsn <= lsn)
		{
			/*
			 * We have to write the changed xmin to disk *before* we change
			 * the in-memory value, otherwise after a crash we wouldn't know
			 * that some catalog tuples might have been removed already.
			 *
			 * Ensure that by first writing to ->xmin and only update
			 * ->effective_xmin once the new state is synced to disk. After a
			 * crash ->effective_xmin is set to ->xmin.
			 */
			if (TransactionIdIsValid(MyReplicationSlot->candidate_catalog_xmin) &&
				MyReplicationSlot->data.catalog_xmin != MyReplicationSlot->candidate_catalog_xmin)
			{
				MyReplicationSlot->data.catalog_xmin = MyReplicationSlot->candidate_catalog_xmin;
				MyReplicationSlot->candidate_catalog_xmin = InvalidTransactionId;
				MyReplicationSlot->candidate_xmin_lsn = InvalidXLogRecPtr;
				updated_xmin = true;
			}
		}

		if (MyReplicationSlot->candidate_restart_valid != InvalidXLogRecPtr &&
			MyReplicationSlot->candidate_restart_valid <= lsn)
		{
			Assert(MyReplicationSlot->candidate_restart_lsn != InvalidXLogRecPtr);

			MyReplicationSlot->data.restart_lsn = MyReplicationSlot->candidate_restart_lsn;
			MyReplicationSlot->candidate_restart_lsn = InvalidXLogRecPtr;
			MyReplicationSlot->candidate_restart_valid = InvalidXLogRecPtr;
			updated_restart = true;
		}

		SpinLockRelease(&MyReplicationSlot->mutex);

		/* first write new xmin to disk, so we know what's up after a crash */
		if (updated_xmin || updated_restart)
		{
			ReplicationSlotMarkDirty();
			ReplicationSlotSave();
			elog(DEBUG1, "updated xmin: %u restart: %u", updated_xmin, updated_restart);
		}

		/*
		 * Now the new xmin is safely on disk, we can let the global value
		 * advance. We do not take ProcArrayLock or similar since we only
		 * advance xmin here and there's not much harm done by a concurrent
		 * computation missing that.
		 */
		if (updated_xmin)
		{
			SpinLockAcquire(&MyReplicationSlot->mutex);
			MyReplicationSlot->effective_catalog_xmin = MyReplicationSlot->data.catalog_xmin;
			SpinLockRelease(&MyReplicationSlot->mutex);

			ReplicationSlotsComputeRequiredXmin(false);
			ReplicationSlotsComputeRequiredLSN();
		}
	}
	else
	{
		SpinLockAcquire(&MyReplicationSlot->mutex);
		MyReplicationSlot->data.confirmed_flush = lsn;
		SpinLockRelease(&MyReplicationSlot->mutex);
	}
}