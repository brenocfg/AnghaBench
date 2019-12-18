#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int xs_temp_snap; int /*<<< orphan*/  parallel_scan; } ;
struct TYPE_11__ {TYPE_1__* rd_indam; } ;
struct TYPE_10__ {TYPE_3__* (* ambeginscan ) (TYPE_2__*,int,int) ;int /*<<< orphan*/  ampredlocks; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  ParallelIndexScanDesc ;
typedef  TYPE_3__* IndexScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_REL_PROCEDURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PredicateLockRelation (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELATION_CHECKS ; 
 int /*<<< orphan*/  RelationIncrementReferenceCount (TYPE_2__*) ; 
 int /*<<< orphan*/  ambeginscan ; 
 TYPE_3__* stub1 (TYPE_2__*,int,int) ; 

__attribute__((used)) static IndexScanDesc
index_beginscan_internal(Relation indexRelation,
						 int nkeys, int norderbys, Snapshot snapshot,
						 ParallelIndexScanDesc pscan, bool temp_snap)
{
	IndexScanDesc scan;

	RELATION_CHECKS;
	CHECK_REL_PROCEDURE(ambeginscan);

	if (!(indexRelation->rd_indam->ampredlocks))
		PredicateLockRelation(indexRelation, snapshot);

	/*
	 * We hold a reference count to the relcache entry throughout the scan.
	 */
	RelationIncrementReferenceCount(indexRelation);

	/*
	 * Tell the AM to open a scan.
	 */
	scan = indexRelation->rd_indam->ambeginscan(indexRelation, nkeys,
												norderbys);
	/* Initialize information for parallel scan. */
	scan->parallel_scan = pscan;
	scan->xs_temp_snap = temp_snap;

	return scan;
}