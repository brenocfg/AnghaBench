#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ TimestampTz ;
struct TYPE_2__ {scalar_t__ current_timestamp; int /*<<< orphan*/  mutex_current; } ;

/* Variables and functions */
 scalar_t__ GetCurrentTimestamp () ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 TYPE_1__* oldSnapshotControl ; 

TimestampTz
GetSnapshotCurrentTimestamp(void)
{
	TimestampTz now = GetCurrentTimestamp();

	/*
	 * Don't let time move backward; if it hasn't advanced, use the old value.
	 */
	SpinLockAcquire(&oldSnapshotControl->mutex_current);
	if (now <= oldSnapshotControl->current_timestamp)
		now = oldSnapshotControl->current_timestamp;
	else
		oldSnapshotControl->current_timestamp = now;
	SpinLockRelease(&oldSnapshotControl->mutex_current);

	return now;
}