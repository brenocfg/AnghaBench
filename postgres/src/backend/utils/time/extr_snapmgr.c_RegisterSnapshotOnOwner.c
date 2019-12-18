#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int regd_count; int /*<<< orphan*/  ph_node; scalar_t__ copied; } ;
typedef  TYPE_1__* Snapshot ;
typedef  int /*<<< orphan*/  ResourceOwner ;

/* Variables and functions */
 TYPE_1__* CopySnapshot (TYPE_1__*) ; 
 TYPE_1__* InvalidSnapshot ; 
 int /*<<< orphan*/  RegisteredSnapshots ; 
 int /*<<< orphan*/  ResourceOwnerEnlargeSnapshots (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResourceOwnerRememberSnapshot (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pairingheap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

Snapshot
RegisterSnapshotOnOwner(Snapshot snapshot, ResourceOwner owner)
{
	Snapshot	snap;

	if (snapshot == InvalidSnapshot)
		return InvalidSnapshot;

	/* Static snapshot?  Create a persistent copy */
	snap = snapshot->copied ? snapshot : CopySnapshot(snapshot);

	/* and tell resowner.c about it */
	ResourceOwnerEnlargeSnapshots(owner);
	snap->regd_count++;
	ResourceOwnerRememberSnapshot(owner, snap);

	if (snap->regd_count == 1)
		pairingheap_add(&RegisteredSnapshots, &snap->ph_node);

	return snap;
}