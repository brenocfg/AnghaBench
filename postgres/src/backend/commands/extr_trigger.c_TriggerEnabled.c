#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  int /*<<< orphan*/  TriggerEvent ;
struct TYPE_14__ {scalar_t__ tgenabled; scalar_t__ tgnattr; int /*<<< orphan*/  tgqual; scalar_t__* tgattr; } ;
typedef  TYPE_2__ Trigger ;
struct TYPE_17__ {int /*<<< orphan*/  es_query_cxt; } ;
struct TYPE_16__ {int /*<<< orphan*/ * ecxt_outertuple; int /*<<< orphan*/ * ecxt_innertuple; } ;
struct TYPE_15__ {int /*<<< orphan*/ ** ri_TrigWhenExprs; TYPE_1__* ri_TrigDesc; } ;
struct TYPE_13__ {TYPE_2__* triggers; } ;
typedef  TYPE_3__ ResultRelInfo ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  TYPE_4__ ExprContext ;
typedef  int /*<<< orphan*/  Expr ;
typedef  TYPE_5__ EState ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ChangeVarNodes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ExecPrepareQual (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  ExecQual (int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ FirstLowInvalidHeapAttributeNumber ; 
 TYPE_4__* GetPerTupleExprContext (TYPE_5__*) ; 
 int /*<<< orphan*/  INNER_VAR ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTER_VAR ; 
 int /*<<< orphan*/  PRS2_NEW_VARNO ; 
 int /*<<< orphan*/  PRS2_OLD_VARNO ; 
 scalar_t__ SESSION_REPLICATION_ROLE_REPLICA ; 
 scalar_t__ SessionReplicationRole ; 
 scalar_t__ TRIGGER_DISABLED ; 
 scalar_t__ TRIGGER_FIRED_BY_UPDATE (int /*<<< orphan*/ ) ; 
 scalar_t__ TRIGGER_FIRES_ON_ORIGIN ; 
 scalar_t__ TRIGGER_FIRES_ON_REPLICA ; 
 scalar_t__ bms_is_member (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ make_ands_implicit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stringToNode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
TriggerEnabled(EState *estate, ResultRelInfo *relinfo,
			   Trigger *trigger, TriggerEvent event,
			   Bitmapset *modifiedCols,
			   TupleTableSlot *oldslot, TupleTableSlot *newslot)
{
	/* Check replication-role-dependent enable state */
	if (SessionReplicationRole == SESSION_REPLICATION_ROLE_REPLICA)
	{
		if (trigger->tgenabled == TRIGGER_FIRES_ON_ORIGIN ||
			trigger->tgenabled == TRIGGER_DISABLED)
			return false;
	}
	else						/* ORIGIN or LOCAL role */
	{
		if (trigger->tgenabled == TRIGGER_FIRES_ON_REPLICA ||
			trigger->tgenabled == TRIGGER_DISABLED)
			return false;
	}

	/*
	 * Check for column-specific trigger (only possible for UPDATE, and in
	 * fact we *must* ignore tgattr for other event types)
	 */
	if (trigger->tgnattr > 0 && TRIGGER_FIRED_BY_UPDATE(event))
	{
		int			i;
		bool		modified;

		modified = false;
		for (i = 0; i < trigger->tgnattr; i++)
		{
			if (bms_is_member(trigger->tgattr[i] - FirstLowInvalidHeapAttributeNumber,
							  modifiedCols))
			{
				modified = true;
				break;
			}
		}
		if (!modified)
			return false;
	}

	/* Check for WHEN clause */
	if (trigger->tgqual)
	{
		ExprState **predicate;
		ExprContext *econtext;
		MemoryContext oldContext;
		int			i;

		Assert(estate != NULL);

		/*
		 * trigger is an element of relinfo->ri_TrigDesc->triggers[]; find the
		 * matching element of relinfo->ri_TrigWhenExprs[]
		 */
		i = trigger - relinfo->ri_TrigDesc->triggers;
		predicate = &relinfo->ri_TrigWhenExprs[i];

		/*
		 * If first time through for this WHEN expression, build expression
		 * nodetrees for it.  Keep them in the per-query memory context so
		 * they'll survive throughout the query.
		 */
		if (*predicate == NULL)
		{
			Node	   *tgqual;

			oldContext = MemoryContextSwitchTo(estate->es_query_cxt);
			tgqual = stringToNode(trigger->tgqual);
			/* Change references to OLD and NEW to INNER_VAR and OUTER_VAR */
			ChangeVarNodes(tgqual, PRS2_OLD_VARNO, INNER_VAR, 0);
			ChangeVarNodes(tgqual, PRS2_NEW_VARNO, OUTER_VAR, 0);
			/* ExecPrepareQual wants implicit-AND form */
			tgqual = (Node *) make_ands_implicit((Expr *) tgqual);
			*predicate = ExecPrepareQual((List *) tgqual, estate);
			MemoryContextSwitchTo(oldContext);
		}

		/*
		 * We will use the EState's per-tuple context for evaluating WHEN
		 * expressions (creating it if it's not already there).
		 */
		econtext = GetPerTupleExprContext(estate);

		/*
		 * Finally evaluate the expression, making the old and/or new tuples
		 * available as INNER_VAR/OUTER_VAR respectively.
		 */
		econtext->ecxt_innertuple = oldslot;
		econtext->ecxt_outertuple = newslot;
		if (!ExecQual(*predicate, econtext))
			return false;
	}

	return true;
}