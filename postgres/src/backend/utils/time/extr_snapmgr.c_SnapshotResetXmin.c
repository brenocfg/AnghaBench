#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  xmin; } ;
struct TYPE_4__ {int /*<<< orphan*/  xmin; } ;
typedef  TYPE_1__* Snapshot ;

/* Variables and functions */
 int /*<<< orphan*/ * ActiveSnapshot ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 TYPE_3__* MyPgXact ; 
 int /*<<< orphan*/  RegisteredSnapshots ; 
 int /*<<< orphan*/  SnapshotData ; 
 scalar_t__ TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* pairingheap_container (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pairingheap_first (int /*<<< orphan*/ *) ; 
 scalar_t__ pairingheap_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ph_node ; 

__attribute__((used)) static void
SnapshotResetXmin(void)
{
	Snapshot	minSnapshot;

	if (ActiveSnapshot != NULL)
		return;

	if (pairingheap_is_empty(&RegisteredSnapshots))
	{
		MyPgXact->xmin = InvalidTransactionId;
		return;
	}

	minSnapshot = pairingheap_container(SnapshotData, ph_node,
										pairingheap_first(&RegisteredSnapshots));

	if (TransactionIdPrecedes(MyPgXact->xmin, minSnapshot->xmin))
		MyPgXact->xmin = minSnapshot->xmin;
}