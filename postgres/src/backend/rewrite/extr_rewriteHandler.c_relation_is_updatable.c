#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {scalar_t__ trig_delete_instead_row; scalar_t__ trig_update_instead_row; scalar_t__ trig_insert_instead_row; } ;
typedef  TYPE_4__ TriggerDesc ;
struct TYPE_30__ {int /*<<< orphan*/  targetList; int /*<<< orphan*/  rtable; TYPE_3__* jointree; } ;
struct TYPE_29__ {scalar_t__ rtekind; scalar_t__ relkind; int /*<<< orphan*/  relid; } ;
struct TYPE_28__ {int /*<<< orphan*/  rtindex; } ;
struct TYPE_27__ {TYPE_2__* rd_rel; TYPE_4__* trigdesc; TYPE_5__* rd_rules; } ;
struct TYPE_26__ {int numLocks; TYPE_1__** rules; } ;
struct TYPE_24__ {int /*<<< orphan*/  fromlist; } ;
struct TYPE_23__ {scalar_t__ relkind; } ;
struct TYPE_22__ {int event; int /*<<< orphan*/ * qual; scalar_t__ isInstead; } ;
struct TYPE_21__ {int (* IsForeignRelUpdatable ) (TYPE_6__*) ;int /*<<< orphan*/ * ExecForeignDelete; int /*<<< orphan*/ * ExecForeignUpdate; int /*<<< orphan*/ * ExecForeignInsert; } ;
typedef  TYPE_5__ RuleLock ;
typedef  TYPE_6__* Relation ;
typedef  TYPE_7__ RangeTblRef ;
typedef  TYPE_8__ RangeTblEntry ;
typedef  TYPE_9__ Query ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_10__ FdwRoutine ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int ALL_EVENTS ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Assert (int) ; 
 int CMD_DELETE ; 
 int CMD_INSERT ; 
 int CMD_UPDATE ; 
 TYPE_10__* GetFdwRoutineForRelation (TYPE_6__*,int) ; 
 scalar_t__ RELKIND_FOREIGN_TABLE ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 scalar_t__ RELKIND_RELATION ; 
 scalar_t__ RELKIND_VIEW ; 
 scalar_t__ RTE_RELATION ; 
 int /*<<< orphan*/ * adjust_view_column_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bms_int_members (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bms_is_empty (int /*<<< orphan*/ *) ; 
 TYPE_9__* get_view_query (TYPE_6__*) ; 
 scalar_t__ linitial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_close (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* rt_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_6__*) ; 
 TYPE_6__* try_relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  view_cols_are_auto_updatable (TYPE_9__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * view_query_is_auto_updatable (TYPE_9__*,int) ; 

int
relation_is_updatable(Oid reloid,
					  bool include_triggers,
					  Bitmapset *include_cols)
{
	int			events = 0;
	Relation	rel;
	RuleLock   *rulelocks;

#define ALL_EVENTS ((1 << CMD_INSERT) | (1 << CMD_UPDATE) | (1 << CMD_DELETE))

	rel = try_relation_open(reloid, AccessShareLock);

	/*
	 * If the relation doesn't exist, return zero rather than throwing an
	 * error.  This is helpful since scanning an information_schema view under
	 * MVCC rules can result in referencing rels that have actually been
	 * deleted already.
	 */
	if (rel == NULL)
		return 0;

	/* If the relation is a table, it is always updatable */
	if (rel->rd_rel->relkind == RELKIND_RELATION ||
		rel->rd_rel->relkind == RELKIND_PARTITIONED_TABLE)
	{
		relation_close(rel, AccessShareLock);
		return ALL_EVENTS;
	}

	/* Look for unconditional DO INSTEAD rules, and note supported events */
	rulelocks = rel->rd_rules;
	if (rulelocks != NULL)
	{
		int			i;

		for (i = 0; i < rulelocks->numLocks; i++)
		{
			if (rulelocks->rules[i]->isInstead &&
				rulelocks->rules[i]->qual == NULL)
			{
				events |= ((1 << rulelocks->rules[i]->event) & ALL_EVENTS);
			}
		}

		/* If we have rules for all events, we're done */
		if (events == ALL_EVENTS)
		{
			relation_close(rel, AccessShareLock);
			return events;
		}
	}

	/* Similarly look for INSTEAD OF triggers, if they are to be included */
	if (include_triggers)
	{
		TriggerDesc *trigDesc = rel->trigdesc;

		if (trigDesc)
		{
			if (trigDesc->trig_insert_instead_row)
				events |= (1 << CMD_INSERT);
			if (trigDesc->trig_update_instead_row)
				events |= (1 << CMD_UPDATE);
			if (trigDesc->trig_delete_instead_row)
				events |= (1 << CMD_DELETE);

			/* If we have triggers for all events, we're done */
			if (events == ALL_EVENTS)
			{
				relation_close(rel, AccessShareLock);
				return events;
			}
		}
	}

	/* If this is a foreign table, check which update events it supports */
	if (rel->rd_rel->relkind == RELKIND_FOREIGN_TABLE)
	{
		FdwRoutine *fdwroutine = GetFdwRoutineForRelation(rel, false);

		if (fdwroutine->IsForeignRelUpdatable != NULL)
			events |= fdwroutine->IsForeignRelUpdatable(rel);
		else
		{
			/* Assume presence of executor functions is sufficient */
			if (fdwroutine->ExecForeignInsert != NULL)
				events |= (1 << CMD_INSERT);
			if (fdwroutine->ExecForeignUpdate != NULL)
				events |= (1 << CMD_UPDATE);
			if (fdwroutine->ExecForeignDelete != NULL)
				events |= (1 << CMD_DELETE);
		}

		relation_close(rel, AccessShareLock);
		return events;
	}

	/* Check if this is an automatically updatable view */
	if (rel->rd_rel->relkind == RELKIND_VIEW)
	{
		Query	   *viewquery = get_view_query(rel);

		if (view_query_is_auto_updatable(viewquery, false) == NULL)
		{
			Bitmapset  *updatable_cols;
			int			auto_events;
			RangeTblRef *rtr;
			RangeTblEntry *base_rte;
			Oid			baseoid;

			/*
			 * Determine which of the view's columns are updatable. If there
			 * are none within the set of columns we are looking at, then the
			 * view doesn't support INSERT/UPDATE, but it may still support
			 * DELETE.
			 */
			view_cols_are_auto_updatable(viewquery, NULL,
										 &updatable_cols, NULL);

			if (include_cols != NULL)
				updatable_cols = bms_int_members(updatable_cols, include_cols);

			if (bms_is_empty(updatable_cols))
				auto_events = (1 << CMD_DELETE);	/* May support DELETE */
			else
				auto_events = ALL_EVENTS;	/* May support all events */

			/*
			 * The base relation must also support these update commands.
			 * Tables are always updatable, but for any other kind of base
			 * relation we must do a recursive check limited to the columns
			 * referenced by the locally updatable columns in this view.
			 */
			rtr = (RangeTblRef *) linitial(viewquery->jointree->fromlist);
			base_rte = rt_fetch(rtr->rtindex, viewquery->rtable);
			Assert(base_rte->rtekind == RTE_RELATION);

			if (base_rte->relkind != RELKIND_RELATION &&
				base_rte->relkind != RELKIND_PARTITIONED_TABLE)
			{
				baseoid = base_rte->relid;
				include_cols = adjust_view_column_set(updatable_cols,
													  viewquery->targetList);
				auto_events &= relation_is_updatable(baseoid,
													 include_triggers,
													 include_cols);
			}
			events |= auto_events;
		}
	}

	/* If we reach here, the relation may support some update commands */
	relation_close(rel, AccessShareLock);
	return events;
}