#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  num_index_tuples; int /*<<< orphan*/  num_pages; } ;
struct TYPE_6__ {int /*<<< orphan*/  index; int /*<<< orphan*/  strategy; scalar_t__ analyze_only; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ IndexVacuumInfo ;
typedef  TYPE_2__ IndexBulkDeleteResult ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  BRIN_ALL_BLOCKRANGES ; 
 int /*<<< orphan*/  IndexGetRelation (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brin_vacuum_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brinsummarize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

IndexBulkDeleteResult *
brinvacuumcleanup(IndexVacuumInfo *info, IndexBulkDeleteResult *stats)
{
	Relation	heapRel;

	/* No-op in ANALYZE ONLY mode */
	if (info->analyze_only)
		return stats;

	if (!stats)
		stats = (IndexBulkDeleteResult *) palloc0(sizeof(IndexBulkDeleteResult));
	stats->num_pages = RelationGetNumberOfBlocks(info->index);
	/* rest of stats is initialized by zeroing */

	heapRel = table_open(IndexGetRelation(RelationGetRelid(info->index), false),
						 AccessShareLock);

	brin_vacuum_scan(info->index, info->strategy);

	brinsummarize(info->index, heapRel, BRIN_ALL_BLOCKRANGES, false,
				  &stats->num_index_tuples, &stats->num_index_tuples);

	table_close(heapRel, AccessShareLock);

	return stats;
}