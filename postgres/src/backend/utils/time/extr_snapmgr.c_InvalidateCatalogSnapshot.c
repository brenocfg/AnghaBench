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
struct TYPE_2__ {int /*<<< orphan*/  ph_node; } ;

/* Variables and functions */
 TYPE_1__* CatalogSnapshot ; 
 int /*<<< orphan*/  RegisteredSnapshots ; 
 int /*<<< orphan*/  SnapshotResetXmin () ; 
 int /*<<< orphan*/  pairingheap_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
InvalidateCatalogSnapshot(void)
{
	if (CatalogSnapshot)
	{
		pairingheap_remove(&RegisteredSnapshots, &CatalogSnapshot->ph_node);
		CatalogSnapshot = NULL;
		SnapshotResetXmin();
	}
}