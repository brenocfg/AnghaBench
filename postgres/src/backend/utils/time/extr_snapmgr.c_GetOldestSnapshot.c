#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_6__ {TYPE_1__* as_snap; } ;
struct TYPE_5__ {scalar_t__ lsn; } ;
typedef  TYPE_1__* Snapshot ;

/* Variables and functions */
 scalar_t__ InvalidXLogRecPtr ; 
 TYPE_3__* OldestActiveSnapshot ; 
 int /*<<< orphan*/  RegisteredSnapshots ; 
 int /*<<< orphan*/  SnapshotData ; 
 scalar_t__ XLogRecPtrIsInvalid (scalar_t__) ; 
 TYPE_1__* pairingheap_container (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pairingheap_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pairingheap_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ph_node ; 

Snapshot
GetOldestSnapshot(void)
{
	Snapshot	OldestRegisteredSnapshot = NULL;
	XLogRecPtr	RegisteredLSN = InvalidXLogRecPtr;

	if (!pairingheap_is_empty(&RegisteredSnapshots))
	{
		OldestRegisteredSnapshot = pairingheap_container(SnapshotData, ph_node,
														 pairingheap_first(&RegisteredSnapshots));
		RegisteredLSN = OldestRegisteredSnapshot->lsn;
	}

	if (OldestActiveSnapshot != NULL)
	{
		XLogRecPtr	ActiveLSN = OldestActiveSnapshot->as_snap->lsn;

		if (XLogRecPtrIsInvalid(RegisteredLSN) || RegisteredLSN > ActiveLSN)
			return OldestActiveSnapshot->as_snap;
	}

	return OldestRegisteredSnapshot;
}