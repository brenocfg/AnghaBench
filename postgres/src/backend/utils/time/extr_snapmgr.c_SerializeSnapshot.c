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
typedef  char TransactionId ;
struct TYPE_6__ {int xcnt; scalar_t__ subxcnt; scalar_t__ suboverflowed; int /*<<< orphan*/  lsn; int /*<<< orphan*/  whenTaken; int /*<<< orphan*/  curcid; int /*<<< orphan*/  takenDuringRecovery; int /*<<< orphan*/  xmax; int /*<<< orphan*/  xmin; } ;
struct TYPE_5__ {scalar_t__ subxcnt; int xcnt; TYPE_2__* subxip; TYPE_2__* xip; int /*<<< orphan*/  takenDuringRecovery; int /*<<< orphan*/  lsn; int /*<<< orphan*/  whenTaken; int /*<<< orphan*/  curcid; scalar_t__ suboverflowed; int /*<<< orphan*/  xmax; int /*<<< orphan*/  xmin; } ;
typedef  TYPE_1__* Snapshot ;
typedef  int Size ;
typedef  TYPE_2__ SerializedSnapshotData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,TYPE_2__*,int) ; 

void
SerializeSnapshot(Snapshot snapshot, char *start_address)
{
	SerializedSnapshotData serialized_snapshot;

	Assert(snapshot->subxcnt >= 0);

	/* Copy all required fields */
	serialized_snapshot.xmin = snapshot->xmin;
	serialized_snapshot.xmax = snapshot->xmax;
	serialized_snapshot.xcnt = snapshot->xcnt;
	serialized_snapshot.subxcnt = snapshot->subxcnt;
	serialized_snapshot.suboverflowed = snapshot->suboverflowed;
	serialized_snapshot.takenDuringRecovery = snapshot->takenDuringRecovery;
	serialized_snapshot.curcid = snapshot->curcid;
	serialized_snapshot.whenTaken = snapshot->whenTaken;
	serialized_snapshot.lsn = snapshot->lsn;

	/*
	 * Ignore the SubXID array if it has overflowed, unless the snapshot was
	 * taken during recovery - in that case, top-level XIDs are in subxip as
	 * well, and we mustn't lose them.
	 */
	if (serialized_snapshot.suboverflowed && !snapshot->takenDuringRecovery)
		serialized_snapshot.subxcnt = 0;

	/* Copy struct to possibly-unaligned buffer */
	memcpy(start_address,
		   &serialized_snapshot, sizeof(SerializedSnapshotData));

	/* Copy XID array */
	if (snapshot->xcnt > 0)
		memcpy((TransactionId *) (start_address +
								  sizeof(SerializedSnapshotData)),
			   snapshot->xip, snapshot->xcnt * sizeof(TransactionId));

	/*
	 * Copy SubXID array. Don't bother to copy it if it had overflowed,
	 * though, because it's not used anywhere in that case. Except if it's a
	 * snapshot taken during recovery; all the top-level XIDs are in subxip as
	 * well in that case, so we mustn't lose them.
	 */
	if (serialized_snapshot.subxcnt > 0)
	{
		Size		subxipoff = sizeof(SerializedSnapshotData) +
		snapshot->xcnt * sizeof(TransactionId);

		memcpy((TransactionId *) (start_address + subxipoff),
			   snapshot->subxip, snapshot->subxcnt * sizeof(TransactionId));
	}
}