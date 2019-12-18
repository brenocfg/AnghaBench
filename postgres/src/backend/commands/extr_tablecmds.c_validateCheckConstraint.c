#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_15__ {int /*<<< orphan*/ * ecxt_scantuple; } ;
struct TYPE_14__ {int /*<<< orphan*/  conname; int /*<<< orphan*/  oid; } ;
struct TYPE_13__ {TYPE_1__* rd_rel; } ;
struct TYPE_12__ {scalar_t__ relkind; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_constraint ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  TYPE_4__ ExprContext ;
typedef  int /*<<< orphan*/  Expr ;
typedef  int /*<<< orphan*/  EState ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_constraint_conbin ; 
 int /*<<< orphan*/  CONSTROID ; 
 int /*<<< orphan*/ * CreateExecutorState () ; 
 int /*<<< orphan*/  ERRCODE_CHECK_VIOLATION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecCheck (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  ExecDropSingleTupleTableSlot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExecPrepareExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  FreeExecutorState (int /*<<< orphan*/ *) ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLatestSnapshot () ; 
 TYPE_4__* GetPerTupleExprContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetPerTupleMemoryContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 scalar_t__ RELKIND_FOREIGN_TABLE ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 int /*<<< orphan*/  RegisterSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetExprContext (TYPE_4__*) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnregisterSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errtableconstraint (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stringToNode (char*) ; 
 int /*<<< orphan*/  table_beginscan (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_endscan (int /*<<< orphan*/ ) ; 
 scalar_t__ table_scan_getnextslot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * table_slot_create (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
validateCheckConstraint(Relation rel, HeapTuple constrtup)
{
	EState	   *estate;
	Datum		val;
	char	   *conbin;
	Expr	   *origexpr;
	ExprState  *exprstate;
	TableScanDesc scan;
	ExprContext *econtext;
	MemoryContext oldcxt;
	TupleTableSlot *slot;
	Form_pg_constraint constrForm;
	bool		isnull;
	Snapshot	snapshot;

	/*
	 * VALIDATE CONSTRAINT is a no-op for foreign tables and partitioned
	 * tables.
	 */
	if (rel->rd_rel->relkind == RELKIND_FOREIGN_TABLE ||
		rel->rd_rel->relkind == RELKIND_PARTITIONED_TABLE)
		return;

	constrForm = (Form_pg_constraint) GETSTRUCT(constrtup);

	estate = CreateExecutorState();

	/*
	 * XXX this tuple doesn't really come from a syscache, but this doesn't
	 * matter to SysCacheGetAttr, because it only wants to be able to fetch
	 * the tupdesc
	 */
	val = SysCacheGetAttr(CONSTROID, constrtup, Anum_pg_constraint_conbin,
						  &isnull);
	if (isnull)
		elog(ERROR, "null conbin for constraint %u",
			 constrForm->oid);
	conbin = TextDatumGetCString(val);
	origexpr = (Expr *) stringToNode(conbin);
	exprstate = ExecPrepareExpr(origexpr, estate);

	econtext = GetPerTupleExprContext(estate);
	slot = table_slot_create(rel, NULL);
	econtext->ecxt_scantuple = slot;

	snapshot = RegisterSnapshot(GetLatestSnapshot());
	scan = table_beginscan(rel, snapshot, 0, NULL);

	/*
	 * Switch to per-tuple memory context and reset it for each tuple
	 * produced, so we don't leak memory.
	 */
	oldcxt = MemoryContextSwitchTo(GetPerTupleMemoryContext(estate));

	while (table_scan_getnextslot(scan, ForwardScanDirection, slot))
	{
		if (!ExecCheck(exprstate, econtext))
			ereport(ERROR,
					(errcode(ERRCODE_CHECK_VIOLATION),
					 errmsg("check constraint \"%s\" is violated by some row",
							NameStr(constrForm->conname)),
					 errtableconstraint(rel, NameStr(constrForm->conname))));

		ResetExprContext(econtext);
	}

	MemoryContextSwitchTo(oldcxt);
	table_endscan(scan);
	UnregisterSnapshot(snapshot);
	ExecDropSingleTupleTableSlot(slot);
	FreeExecutorState(estate);
}