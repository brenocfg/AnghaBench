#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ XLogRecPtr ;
typedef  void* TransactionId ;
struct TYPE_4__ {scalar_t__ confirmed_flush; int /*<<< orphan*/  catalog_xmin; } ;
struct TYPE_5__ {scalar_t__ candidate_xmin_lsn; TYPE_1__ data; int /*<<< orphan*/  mutex; void* candidate_catalog_xmin; } ;
typedef  TYPE_2__ ReplicationSlot ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidXLogRecPtr ; 
 int /*<<< orphan*/  LogicalConfirmReceivedLocation (scalar_t__) ; 
 TYPE_2__* MyReplicationSlot ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 scalar_t__ TransactionIdPrecedesOrEquals (void*,int /*<<< orphan*/ ) ; 

void
LogicalIncreaseXminForSlot(XLogRecPtr current_lsn, TransactionId xmin)
{
	bool		updated_xmin = false;
	ReplicationSlot *slot;

	slot = MyReplicationSlot;

	Assert(slot != NULL);

	SpinLockAcquire(&slot->mutex);

	/*
	 * don't overwrite if we already have a newer xmin. This can happen if we
	 * restart decoding in a slot.
	 */
	if (TransactionIdPrecedesOrEquals(xmin, slot->data.catalog_xmin))
	{
	}

	/*
	 * If the client has already confirmed up to this lsn, we directly can
	 * mark this as accepted. This can happen if we restart decoding in a
	 * slot.
	 */
	else if (current_lsn <= slot->data.confirmed_flush)
	{
		slot->candidate_catalog_xmin = xmin;
		slot->candidate_xmin_lsn = current_lsn;

		/* our candidate can directly be used */
		updated_xmin = true;
	}

	/*
	 * Only increase if the previous values have been applied, otherwise we
	 * might never end up updating if the receiver acks too slowly.
	 */
	else if (slot->candidate_xmin_lsn == InvalidXLogRecPtr)
	{
		slot->candidate_catalog_xmin = xmin;
		slot->candidate_xmin_lsn = current_lsn;
	}
	SpinLockRelease(&slot->mutex);

	/* candidate already valid with the current flush position, apply */
	if (updated_xmin)
		LogicalConfirmReceivedLocation(slot->data.confirmed_flush);
}