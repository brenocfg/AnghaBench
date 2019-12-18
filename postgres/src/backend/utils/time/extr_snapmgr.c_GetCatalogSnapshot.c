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
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  GetNonHistoricCatalogSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HistoricSnapshot ; 
 scalar_t__ HistoricSnapshotActive () ; 

Snapshot
GetCatalogSnapshot(Oid relid)
{
	/*
	 * Return historic snapshot while we're doing logical decoding, so we can
	 * see the appropriate state of the catalog.
	 *
	 * This is the primary reason for needing to reset the system caches after
	 * finishing decoding.
	 */
	if (HistoricSnapshotActive())
		return HistoricSnapshot;

	return GetNonHistoricCatalogSnapshot(relid);
}