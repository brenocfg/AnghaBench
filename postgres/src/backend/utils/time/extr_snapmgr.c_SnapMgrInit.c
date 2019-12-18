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
struct TYPE_3__ {scalar_t__ count_used; scalar_t__ head_timestamp; scalar_t__ head_offset; void* threshold_xid; scalar_t__ threshold_timestamp; int /*<<< orphan*/  mutex_threshold; scalar_t__ next_map_update; void* latest_xmin; int /*<<< orphan*/  mutex_latest_xmin; scalar_t__ current_timestamp; int /*<<< orphan*/  mutex_current; } ;
typedef  TYPE_1__ OldSnapshotControlData ;

/* Variables and functions */
 void* InvalidTransactionId ; 
 scalar_t__ ShmemInitStruct (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  SnapMgrShmemSize () ; 
 int /*<<< orphan*/  SpinLockInit (int /*<<< orphan*/ *) ; 
 TYPE_1__ volatile* oldSnapshotControl ; 

void
SnapMgrInit(void)
{
	bool		found;

	/*
	 * Create or attach to the OldSnapshotControlData structure.
	 */
	oldSnapshotControl = (volatile OldSnapshotControlData *)
		ShmemInitStruct("OldSnapshotControlData",
						SnapMgrShmemSize(), &found);

	if (!found)
	{
		SpinLockInit(&oldSnapshotControl->mutex_current);
		oldSnapshotControl->current_timestamp = 0;
		SpinLockInit(&oldSnapshotControl->mutex_latest_xmin);
		oldSnapshotControl->latest_xmin = InvalidTransactionId;
		oldSnapshotControl->next_map_update = 0;
		SpinLockInit(&oldSnapshotControl->mutex_threshold);
		oldSnapshotControl->threshold_timestamp = 0;
		oldSnapshotControl->threshold_xid = InvalidTransactionId;
		oldSnapshotControl->head_offset = 0;
		oldSnapshotControl->head_timestamp = 0;
		oldSnapshotControl->count_used = 0;
	}
}