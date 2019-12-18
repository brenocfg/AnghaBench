#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* TransactionId ;
struct TYPE_7__ {int /*<<< orphan*/  xmin; } ;
struct TYPE_5__ {void* xmin; void* catalog_xmin; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; void* effective_catalog_xmin; TYPE_1__ data; void* effective_xmin; } ;
typedef  TYPE_2__ ReplicationSlot ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidTransactionId ; 
 TYPE_4__* MyPgXact ; 
 TYPE_2__* MyReplicationSlot ; 
 int /*<<< orphan*/  ReplicationSlotMarkDirty () ; 
 int /*<<< orphan*/  ReplicationSlotsComputeRequiredXmin (int) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TransactionIdIsNormal (void*) ; 
 scalar_t__ TransactionIdPrecedes (void*,void*) ; 

__attribute__((used)) static void
PhysicalReplicationSlotNewXmin(TransactionId feedbackXmin, TransactionId feedbackCatalogXmin)
{
	bool		changed = false;
	ReplicationSlot *slot = MyReplicationSlot;

	SpinLockAcquire(&slot->mutex);
	MyPgXact->xmin = InvalidTransactionId;

	/*
	 * For physical replication we don't need the interlock provided by xmin
	 * and effective_xmin since the consequences of a missed increase are
	 * limited to query cancellations, so set both at once.
	 */
	if (!TransactionIdIsNormal(slot->data.xmin) ||
		!TransactionIdIsNormal(feedbackXmin) ||
		TransactionIdPrecedes(slot->data.xmin, feedbackXmin))
	{
		changed = true;
		slot->data.xmin = feedbackXmin;
		slot->effective_xmin = feedbackXmin;
	}
	if (!TransactionIdIsNormal(slot->data.catalog_xmin) ||
		!TransactionIdIsNormal(feedbackCatalogXmin) ||
		TransactionIdPrecedes(slot->data.catalog_xmin, feedbackCatalogXmin))
	{
		changed = true;
		slot->data.catalog_xmin = feedbackCatalogXmin;
		slot->effective_catalog_xmin = feedbackCatalogXmin;
	}
	SpinLockRelease(&slot->mutex);

	if (changed)
	{
		ReplicationSlotMarkDirty();
		ReplicationSlotsComputeRequiredXmin(false);
	}
}