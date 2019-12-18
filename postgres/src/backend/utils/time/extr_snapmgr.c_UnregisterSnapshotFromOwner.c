#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ regd_count; scalar_t__ active_count; int /*<<< orphan*/  ph_node; } ;
typedef  TYPE_1__* Snapshot ;
typedef  int /*<<< orphan*/  ResourceOwner ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  FreeSnapshot (TYPE_1__*) ; 
 int /*<<< orphan*/  RegisteredSnapshots ; 
 int /*<<< orphan*/  ResourceOwnerForgetSnapshot (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SnapshotResetXmin () ; 
 int /*<<< orphan*/  pairingheap_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pairingheap_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
UnregisterSnapshotFromOwner(Snapshot snapshot, ResourceOwner owner)
{
	if (snapshot == NULL)
		return;

	Assert(snapshot->regd_count > 0);
	Assert(!pairingheap_is_empty(&RegisteredSnapshots));

	ResourceOwnerForgetSnapshot(owner, snapshot);

	snapshot->regd_count--;
	if (snapshot->regd_count == 0)
		pairingheap_remove(&RegisteredSnapshots, &snapshot->ph_node);

	if (snapshot->regd_count == 0 && snapshot->active_count == 0)
	{
		FreeSnapshot(snapshot);
		SnapshotResetXmin();
	}
}