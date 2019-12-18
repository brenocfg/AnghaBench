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
struct TYPE_3__ {scalar_t__ restart_lsn; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; TYPE_1__ data; } ;

/* Variables and functions */
 TYPE_2__* MyReplicationSlot ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 

__attribute__((used)) static XLogRecPtr
pg_physical_replication_slot_advance(XLogRecPtr moveto)
{
	XLogRecPtr	startlsn = MyReplicationSlot->data.restart_lsn;
	XLogRecPtr	retlsn = startlsn;

	if (startlsn < moveto)
	{
		SpinLockAcquire(&MyReplicationSlot->mutex);
		MyReplicationSlot->data.restart_lsn = moveto;
		SpinLockRelease(&MyReplicationSlot->mutex);
		retlsn = moveto;
	}

	return retlsn;
}