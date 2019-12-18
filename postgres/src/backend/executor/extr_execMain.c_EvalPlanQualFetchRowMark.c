#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_17__ {TYPE_1__* rd_rel; } ;
struct TYPE_16__ {int /*<<< orphan*/ * origslot; int /*<<< orphan*/  recheckestate; TYPE_4__** relsubs_rowmark; } ;
struct TYPE_15__ {int /*<<< orphan*/  wholeAttNo; int /*<<< orphan*/  ctidAttNo; int /*<<< orphan*/  toidAttNo; TYPE_3__* rowmark; } ;
struct TYPE_14__ {scalar_t__ markType; scalar_t__ rti; scalar_t__ prti; scalar_t__ relid; TYPE_6__* relation; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* RefetchForeignRow ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ;} ;
struct TYPE_12__ {scalar_t__ relkind; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int Index ;
typedef  TYPE_2__ FdwRoutine ;
typedef  TYPE_3__ ExecRowMark ;
typedef  TYPE_4__ ExecAuxRowMark ;
typedef  TYPE_5__ EPQState ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DatumGetObjectId (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecGetJunkAttribute (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ExecStoreHeapTupleDatum (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* GetFdwRoutineForRelation (TYPE_6__*,int) ; 
 int OidIsValid (scalar_t__) ; 
 scalar_t__ RELKIND_FOREIGN_TABLE ; 
 scalar_t__ ROW_MARK_COPY ; 
 scalar_t__ ROW_MARK_REFERENCE ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_6__*) ; 
 scalar_t__ RowMarkRequiresRowShareLock (scalar_t__) ; 
 int /*<<< orphan*/  SnapshotAny ; 
 scalar_t__ TupIsNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  table_tuple_fetch_row_version (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool
EvalPlanQualFetchRowMark(EPQState *epqstate, Index rti, TupleTableSlot *slot)
{
	ExecAuxRowMark *earm = epqstate->relsubs_rowmark[rti - 1];
	ExecRowMark *erm = earm->rowmark;
	Datum		datum;
	bool		isNull;

	Assert(earm != NULL);
	Assert(epqstate->origslot != NULL);

	if (RowMarkRequiresRowShareLock(erm->markType))
		elog(ERROR, "EvalPlanQual doesn't support locking rowmarks");

	/* if child rel, must check whether it produced this row */
	if (erm->rti != erm->prti)
	{
		Oid			tableoid;

		datum = ExecGetJunkAttribute(epqstate->origslot,
									 earm->toidAttNo,
									 &isNull);
		/* non-locked rels could be on the inside of outer joins */
		if (isNull)
			return false;

		tableoid = DatumGetObjectId(datum);

		Assert(OidIsValid(erm->relid));
		if (tableoid != erm->relid)
		{
			/* this child is inactive right now */
			return false;
		}
	}

	if (erm->markType == ROW_MARK_REFERENCE)
	{
		Assert(erm->relation != NULL);

		/* fetch the tuple's ctid */
		datum = ExecGetJunkAttribute(epqstate->origslot,
									 earm->ctidAttNo,
									 &isNull);
		/* non-locked rels could be on the inside of outer joins */
		if (isNull)
			return false;

		/* fetch requests on foreign tables must be passed to their FDW */
		if (erm->relation->rd_rel->relkind == RELKIND_FOREIGN_TABLE)
		{
			FdwRoutine *fdwroutine;
			bool		updated = false;

			fdwroutine = GetFdwRoutineForRelation(erm->relation, false);
			/* this should have been checked already, but let's be safe */
			if (fdwroutine->RefetchForeignRow == NULL)
				ereport(ERROR,
						(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						 errmsg("cannot lock rows in foreign table \"%s\"",
								RelationGetRelationName(erm->relation))));

			fdwroutine->RefetchForeignRow(epqstate->recheckestate,
										  erm,
										  datum,
										  slot,
										  &updated);
			if (TupIsNull(slot))
				elog(ERROR, "failed to fetch tuple for EvalPlanQual recheck");

			/*
			 * Ideally we'd insist on updated == false here, but that assumes
			 * that FDWs can track that exactly, which they might not be able
			 * to.  So just ignore the flag.
			 */
			return true;
		}
		else
		{
			/* ordinary table, fetch the tuple */
			if (!table_tuple_fetch_row_version(erm->relation,
											   (ItemPointer) DatumGetPointer(datum),
											   SnapshotAny, slot))
				elog(ERROR, "failed to fetch tuple for EvalPlanQual recheck");
			return true;
		}
	}
	else
	{
		Assert(erm->markType == ROW_MARK_COPY);

		/* fetch the whole-row Var for the relation */
		datum = ExecGetJunkAttribute(epqstate->origslot,
									 earm->wholeAttNo,
									 &isNull);
		/* non-locked rels could be on the inside of outer joins */
		if (isNull)
			return false;

		ExecStoreHeapTupleDatum(datum, slot);
		return true;
	}
}