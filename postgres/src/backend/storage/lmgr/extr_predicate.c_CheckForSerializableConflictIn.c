#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_7__ {int /*<<< orphan*/  dbNode; } ;
struct TYPE_8__ {int /*<<< orphan*/  rd_id; TYPE_1__ rd_node; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  PREDICATELOCKTARGETTAG ;
typedef  TYPE_3__* HeapTuple ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckTargetForConflictsIn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERRCODE_T_R_SERIALIZATION_FAILURE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerGetOffsetNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MySerializableXact ; 
 int MyXactDidWrite ; 
 int /*<<< orphan*/  SET_PREDICATELOCKTARGETTAG_PAGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_PREDICATELOCKTARGETTAG_RELATION (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_PREDICATELOCKTARGETTAG_TUPLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SerializationNeededForWrite (TYPE_2__*) ; 
 scalar_t__ SxactIsDoomed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_internal (char*) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

void
CheckForSerializableConflictIn(Relation relation, HeapTuple tuple,
							   Buffer buffer)
{
	PREDICATELOCKTARGETTAG targettag;

	if (!SerializationNeededForWrite(relation))
		return;

	/* Check if someone else has already decided that we need to die */
	if (SxactIsDoomed(MySerializableXact))
		ereport(ERROR,
				(errcode(ERRCODE_T_R_SERIALIZATION_FAILURE),
				 errmsg("could not serialize access due to read/write dependencies among transactions"),
				 errdetail_internal("Reason code: Canceled on identification as a pivot, during conflict in checking."),
				 errhint("The transaction might succeed if retried.")));

	/*
	 * We're doing a write which might cause rw-conflicts now or later.
	 * Memorize that fact.
	 */
	MyXactDidWrite = true;

	/*
	 * It is important that we check for locks from the finest granularity to
	 * the coarsest granularity, so that granularity promotion doesn't cause
	 * us to miss a lock.  The new (coarser) lock will be acquired before the
	 * old (finer) locks are released.
	 *
	 * It is not possible to take and hold a lock across the checks for all
	 * granularities because each target could be in a separate partition.
	 */
	if (tuple != NULL)
	{
		SET_PREDICATELOCKTARGETTAG_TUPLE(targettag,
										 relation->rd_node.dbNode,
										 relation->rd_id,
										 ItemPointerGetBlockNumber(&(tuple->t_self)),
										 ItemPointerGetOffsetNumber(&(tuple->t_self)));
		CheckTargetForConflictsIn(&targettag);
	}

	if (BufferIsValid(buffer))
	{
		SET_PREDICATELOCKTARGETTAG_PAGE(targettag,
										relation->rd_node.dbNode,
										relation->rd_id,
										BufferGetBlockNumber(buffer));
		CheckTargetForConflictsIn(&targettag);
	}

	SET_PREDICATELOCKTARGETTAG_RELATION(targettag,
										relation->rd_node.dbNode,
										relation->rd_id);
	CheckTargetForConflictsIn(&targettag);
}