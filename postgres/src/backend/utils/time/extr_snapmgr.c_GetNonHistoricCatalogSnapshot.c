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
struct TYPE_5__ {int /*<<< orphan*/  ph_node; } ;
typedef  TYPE_1__* Snapshot ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 TYPE_1__* CatalogSnapshot ; 
 int /*<<< orphan*/  CatalogSnapshotData ; 
 TYPE_1__* GetSnapshotData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidateCatalogSnapshot () ; 
 int /*<<< orphan*/  RegisteredSnapshots ; 
 int /*<<< orphan*/  RelationHasSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationInvalidatesSnapshotsOnly (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pairingheap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

Snapshot
GetNonHistoricCatalogSnapshot(Oid relid)
{
	/*
	 * If the caller is trying to scan a relation that has no syscache, no
	 * catcache invalidations will be sent when it is updated.  For a few key
	 * relations, snapshot invalidations are sent instead.  If we're trying to
	 * scan a relation for which neither catcache nor snapshot invalidations
	 * are sent, we must refresh the snapshot every time.
	 */
	if (CatalogSnapshot &&
		!RelationInvalidatesSnapshotsOnly(relid) &&
		!RelationHasSysCache(relid))
		InvalidateCatalogSnapshot();

	if (CatalogSnapshot == NULL)
	{
		/* Get new snapshot. */
		CatalogSnapshot = GetSnapshotData(&CatalogSnapshotData);

		/*
		 * Make sure the catalog snapshot will be accounted for in decisions
		 * about advancing PGXACT->xmin.  We could apply RegisterSnapshot, but
		 * that would result in making a physical copy, which is overkill; and
		 * it would also create a dependency on some resource owner, which we
		 * do not want for reasons explained at the head of this file. Instead
		 * just shove the CatalogSnapshot into the pairing heap manually. This
		 * has to be reversed in InvalidateCatalogSnapshot, of course.
		 *
		 * NB: it had better be impossible for this to throw error, since the
		 * CatalogSnapshot pointer is already valid.
		 */
		pairingheap_add(&RegisteredSnapshots, &CatalogSnapshot->ph_node);
	}

	return CatalogSnapshot;
}