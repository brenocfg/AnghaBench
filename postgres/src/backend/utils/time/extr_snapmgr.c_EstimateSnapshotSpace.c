#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_4__ {scalar_t__ snapshot_type; scalar_t__ xcnt; scalar_t__ subxcnt; scalar_t__ takenDuringRecovery; int /*<<< orphan*/  suboverflowed; } ;
typedef  TYPE_1__* Snapshot ;
typedef  int Size ;
typedef  int /*<<< orphan*/  SerializedSnapshotData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_1__* InvalidSnapshot ; 
 scalar_t__ SNAPSHOT_MVCC ; 
 int add_size (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mul_size (scalar_t__,int) ; 

Size
EstimateSnapshotSpace(Snapshot snap)
{
	Size		size;

	Assert(snap != InvalidSnapshot);
	Assert(snap->snapshot_type == SNAPSHOT_MVCC);

	/* We allocate any XID arrays needed in the same palloc block. */
	size = add_size(sizeof(SerializedSnapshotData),
					mul_size(snap->xcnt, sizeof(TransactionId)));
	if (snap->subxcnt > 0 &&
		(!snap->suboverflowed || snap->takenDuringRecovery))
		size = add_size(size,
						mul_size(snap->subxcnt, sizeof(TransactionId)));

	return size;
}