#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_20__ {int /*<<< orphan*/  es_tupleTable; int /*<<< orphan*/  es_result_relation_info; } ;
struct TYPE_19__ {int /*<<< orphan*/  localrel; } ;
struct TYPE_18__ {int /*<<< orphan*/  values; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ LogicalRepTupleData ;
typedef  TYPE_2__ LogicalRepRelMapEntry ;
typedef  int /*<<< orphan*/  LogicalRepRelId ;
typedef  TYPE_3__ EState ;

/* Variables and functions */
 int /*<<< orphan*/  AfterTriggerEndQuery (TYPE_3__*) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  ExecCloseIndices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ExecInitExtraTupleSlot (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecOpenIndices (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ExecResetTupleTable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ExecSimpleRelationInsert (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeExecutorState (TYPE_3__*) ; 
 int /*<<< orphan*/  GetPerTupleMemoryContext (TYPE_3__*) ; 
 int /*<<< orphan*/  GetTransactionSnapshot () ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  PopActiveSnapshot () ; 
 int /*<<< orphan*/  PushActiveSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  TTSOpsVirtual ; 
 TYPE_3__* create_estate_for_relation (TYPE_2__*) ; 
 int /*<<< orphan*/  ensure_transaction () ; 
 int /*<<< orphan*/  logicalrep_read_insert (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  logicalrep_rel_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* logicalrep_rel_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  should_apply_changes_for_rel (TYPE_2__*) ; 
 int /*<<< orphan*/  slot_fill_defaults (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slot_store_cstrings (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
apply_handle_insert(StringInfo s)
{
	LogicalRepRelMapEntry *rel;
	LogicalRepTupleData newtup;
	LogicalRepRelId relid;
	EState	   *estate;
	TupleTableSlot *remoteslot;
	MemoryContext oldctx;

	ensure_transaction();

	relid = logicalrep_read_insert(s, &newtup);
	rel = logicalrep_rel_open(relid, RowExclusiveLock);
	if (!should_apply_changes_for_rel(rel))
	{
		/*
		 * The relation can't become interesting in the middle of the
		 * transaction so it's safe to unlock it.
		 */
		logicalrep_rel_close(rel, RowExclusiveLock);
		return;
	}

	/* Initialize the executor state. */
	estate = create_estate_for_relation(rel);
	remoteslot = ExecInitExtraTupleSlot(estate,
										RelationGetDescr(rel->localrel),
										&TTSOpsVirtual);

	/* Input functions may need an active snapshot, so get one */
	PushActiveSnapshot(GetTransactionSnapshot());

	/* Process and store remote tuple in the slot */
	oldctx = MemoryContextSwitchTo(GetPerTupleMemoryContext(estate));
	slot_store_cstrings(remoteslot, rel, newtup.values);
	slot_fill_defaults(rel, estate, remoteslot);
	MemoryContextSwitchTo(oldctx);

	ExecOpenIndices(estate->es_result_relation_info, false);

	/* Do the insert. */
	ExecSimpleRelationInsert(estate, remoteslot);

	/* Cleanup. */
	ExecCloseIndices(estate->es_result_relation_info);
	PopActiveSnapshot();

	/* Handle queued AFTER triggers. */
	AfterTriggerEndQuery(estate);

	ExecResetTupleTable(estate->es_tupleTable, false);
	FreeExecutorState(estate);

	logicalrep_rel_close(rel, NoLock);

	CommandCounterIncrement();
}