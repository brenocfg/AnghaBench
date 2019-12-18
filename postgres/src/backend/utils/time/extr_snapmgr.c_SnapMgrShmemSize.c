#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
typedef  int /*<<< orphan*/  Size ;

/* Variables and functions */
 int /*<<< orphan*/  OLD_SNAPSHOT_TIME_MAP_ENTRIES ; 
 int /*<<< orphan*/  OldSnapshotControlData ; 
 int /*<<< orphan*/  add_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mul_size (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ old_snapshot_threshold ; 
 int /*<<< orphan*/  xid_by_minute ; 

Size
SnapMgrShmemSize(void)
{
	Size		size;

	size = offsetof(OldSnapshotControlData, xid_by_minute);
	if (old_snapshot_threshold > 0)
		size = add_size(size, mul_size(sizeof(TransactionId),
									   OLD_SNAPSHOT_TIME_MAP_ENTRIES));

	return size;
}