#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__* rd_rel; int /*<<< orphan*/  trigdesc; } ;
struct TYPE_13__ {int ri_usesFdwDirectModify; int /*<<< orphan*/ * ri_CopyMultiInsertBuffer; int /*<<< orphan*/ * ri_PartitionInfo; TYPE_3__* ri_PartitionRoot; int /*<<< orphan*/ * ri_PartitionCheck; int /*<<< orphan*/ * ri_TrigNewSlot; int /*<<< orphan*/ * ri_TrigOldSlot; int /*<<< orphan*/ * ri_ReturningSlot; int /*<<< orphan*/ * ri_onConflict; void* ri_onConflictArbiterIndexes; int /*<<< orphan*/ * ri_projectReturning; int /*<<< orphan*/ * ri_junkFilter; int /*<<< orphan*/ * ri_GeneratedExprs; int /*<<< orphan*/ * ri_ConstraintExprs; int /*<<< orphan*/ * ri_FdwState; int /*<<< orphan*/ * ri_FdwRoutine; int /*<<< orphan*/ * ri_TrigInstrument; int /*<<< orphan*/ ** ri_TrigWhenExprs; int /*<<< orphan*/ * ri_TrigFunctions; TYPE_10__* ri_TrigDesc; int /*<<< orphan*/ * ri_IndexRelationInfo; int /*<<< orphan*/ * ri_IndexRelationDescs; scalar_t__ ri_NumIndices; TYPE_3__* ri_RelationDesc; int /*<<< orphan*/  ri_RangeTableIndex; int /*<<< orphan*/  type; } ;
struct TYPE_12__ {scalar_t__ relkind; } ;
struct TYPE_11__ {int numtriggers; } ;
typedef  TYPE_2__ ResultRelInfo ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Index ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  ExprState ;

/* Variables and functions */
 TYPE_10__* CopyTriggerDesc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetFdwRoutineForRelation (TYPE_3__*,int) ; 
 int /*<<< orphan*/ * InstrAlloc (int,int) ; 
 int /*<<< orphan*/  MemSet (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 void* NIL ; 
 scalar_t__ RELKIND_FOREIGN_TABLE ; 
 int /*<<< orphan*/ * RelationGetPartitionQual (TYPE_3__*) ; 
 int /*<<< orphan*/  T_ResultRelInfo ; 
 scalar_t__ palloc0 (int) ; 

void
InitResultRelInfo(ResultRelInfo *resultRelInfo,
				  Relation resultRelationDesc,
				  Index resultRelationIndex,
				  Relation partition_root,
				  int instrument_options)
{
	List	   *partition_check = NIL;

	MemSet(resultRelInfo, 0, sizeof(ResultRelInfo));
	resultRelInfo->type = T_ResultRelInfo;
	resultRelInfo->ri_RangeTableIndex = resultRelationIndex;
	resultRelInfo->ri_RelationDesc = resultRelationDesc;
	resultRelInfo->ri_NumIndices = 0;
	resultRelInfo->ri_IndexRelationDescs = NULL;
	resultRelInfo->ri_IndexRelationInfo = NULL;
	/* make a copy so as not to depend on relcache info not changing... */
	resultRelInfo->ri_TrigDesc = CopyTriggerDesc(resultRelationDesc->trigdesc);
	if (resultRelInfo->ri_TrigDesc)
	{
		int			n = resultRelInfo->ri_TrigDesc->numtriggers;

		resultRelInfo->ri_TrigFunctions = (FmgrInfo *)
			palloc0(n * sizeof(FmgrInfo));
		resultRelInfo->ri_TrigWhenExprs = (ExprState **)
			palloc0(n * sizeof(ExprState *));
		if (instrument_options)
			resultRelInfo->ri_TrigInstrument = InstrAlloc(n, instrument_options);
	}
	else
	{
		resultRelInfo->ri_TrigFunctions = NULL;
		resultRelInfo->ri_TrigWhenExprs = NULL;
		resultRelInfo->ri_TrigInstrument = NULL;
	}
	if (resultRelationDesc->rd_rel->relkind == RELKIND_FOREIGN_TABLE)
		resultRelInfo->ri_FdwRoutine = GetFdwRoutineForRelation(resultRelationDesc, true);
	else
		resultRelInfo->ri_FdwRoutine = NULL;

	/* The following fields are set later if needed */
	resultRelInfo->ri_FdwState = NULL;
	resultRelInfo->ri_usesFdwDirectModify = false;
	resultRelInfo->ri_ConstraintExprs = NULL;
	resultRelInfo->ri_GeneratedExprs = NULL;
	resultRelInfo->ri_junkFilter = NULL;
	resultRelInfo->ri_projectReturning = NULL;
	resultRelInfo->ri_onConflictArbiterIndexes = NIL;
	resultRelInfo->ri_onConflict = NULL;
	resultRelInfo->ri_ReturningSlot = NULL;
	resultRelInfo->ri_TrigOldSlot = NULL;
	resultRelInfo->ri_TrigNewSlot = NULL;

	/*
	 * Partition constraint, which also includes the partition constraint of
	 * all the ancestors that are partitions.  Note that it will be checked
	 * even in the case of tuple-routing where this table is the target leaf
	 * partition, if there any BR triggers defined on the table.  Although
	 * tuple-routing implicitly preserves the partition constraint of the
	 * target partition for a given row, the BR triggers may change the row
	 * such that the constraint is no longer satisfied, which we must fail for
	 * by checking it explicitly.
	 *
	 * If this is a partitioned table, the partition constraint (if any) of a
	 * given row will be checked just before performing tuple-routing.
	 */
	partition_check = RelationGetPartitionQual(resultRelationDesc);

	resultRelInfo->ri_PartitionCheck = partition_check;
	resultRelInfo->ri_PartitionRoot = partition_root;
	resultRelInfo->ri_PartitionInfo = NULL; /* may be set later */
	resultRelInfo->ri_CopyMultiInsertBuffer = NULL;
}