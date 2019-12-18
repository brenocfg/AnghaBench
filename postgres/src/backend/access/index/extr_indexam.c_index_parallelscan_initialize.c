#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  ps_snapshot_data; int /*<<< orphan*/  ps_offset; void* ps_indexid; void* ps_relid; } ;
struct TYPE_10__ {TYPE_1__* rd_indam; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* aminitparallelscan ) (void*) ;} ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Size ;
typedef  TYPE_2__* Relation ;
typedef  TYPE_3__* ParallelIndexScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  EstimateSnapshotSpace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAXALIGN (int /*<<< orphan*/ ) ; 
 void* OffsetToPointer (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ParallelIndexScanDescData ; 
 int /*<<< orphan*/  RELATION_CHECKS ; 
 void* RelationGetRelid (TYPE_2__*) ; 
 int /*<<< orphan*/  SerializeSnapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps_snapshot_data ; 
 int /*<<< orphan*/  stub1 (void*) ; 

void
index_parallelscan_initialize(Relation heapRelation, Relation indexRelation,
							  Snapshot snapshot, ParallelIndexScanDesc target)
{
	Size		offset;

	RELATION_CHECKS;

	offset = add_size(offsetof(ParallelIndexScanDescData, ps_snapshot_data),
					  EstimateSnapshotSpace(snapshot));
	offset = MAXALIGN(offset);

	target->ps_relid = RelationGetRelid(heapRelation);
	target->ps_indexid = RelationGetRelid(indexRelation);
	target->ps_offset = offset;
	SerializeSnapshot(snapshot, target->ps_snapshot_data);

	/* aminitparallelscan is optional; assume no-op if not provided by AM */
	if (indexRelation->rd_indam->aminitparallelscan != NULL)
	{
		void	   *amtarget;

		amtarget = OffsetToPointer(target, offset);
		indexRelation->rd_indam->aminitparallelscan(amtarget);
	}
}