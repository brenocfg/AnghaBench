#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Var ;
typedef  int /*<<< orphan*/  TargetEntry ;
struct TYPE_16__ {int /*<<< orphan*/  (* AddForeignUpdateTargets ) (TYPE_4__*,int /*<<< orphan*/ *,TYPE_3__*) ;} ;
struct TYPE_15__ {scalar_t__ commandType; int /*<<< orphan*/  targetList; int /*<<< orphan*/  resultRelation; } ;
struct TYPE_14__ {TYPE_2__* trigdesc; TYPE_1__* rd_rel; } ;
struct TYPE_13__ {scalar_t__ trig_delete_before_row; scalar_t__ trig_delete_after_row; scalar_t__ trig_update_before_row; scalar_t__ trig_update_after_row; } ;
struct TYPE_12__ {scalar_t__ relkind; } ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  RangeTblEntry ;
typedef  TYPE_4__ Query ;
typedef  TYPE_5__ FdwRoutine ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 scalar_t__ CMD_DELETE ; 
 scalar_t__ CMD_UPDATE ; 
 TYPE_5__* GetFdwRoutineForRelation (TYPE_3__*,int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ RELKIND_FOREIGN_TABLE ; 
 scalar_t__ RELKIND_MATVIEW ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 scalar_t__ RELKIND_RELATION ; 
 int /*<<< orphan*/  SelfItemPointerAttributeNumber ; 
 int /*<<< orphan*/  TIDOID ; 
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * makeTargetEntry (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * makeVar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * makeWholeRowVar (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pstrdup (char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ *,TYPE_3__*) ; 

void
rewriteTargetListUD(Query *parsetree, RangeTblEntry *target_rte,
					Relation target_relation)
{
	Var		   *var = NULL;
	const char *attrname;
	TargetEntry *tle;

	if (target_relation->rd_rel->relkind == RELKIND_RELATION ||
		target_relation->rd_rel->relkind == RELKIND_MATVIEW ||
		target_relation->rd_rel->relkind == RELKIND_PARTITIONED_TABLE)
	{
		/*
		 * Emit CTID so that executor can find the row to update or delete.
		 */
		var = makeVar(parsetree->resultRelation,
					  SelfItemPointerAttributeNumber,
					  TIDOID,
					  -1,
					  InvalidOid,
					  0);

		attrname = "ctid";
	}
	else if (target_relation->rd_rel->relkind == RELKIND_FOREIGN_TABLE)
	{
		/*
		 * Let the foreign table's FDW add whatever junk TLEs it wants.
		 */
		FdwRoutine *fdwroutine;

		fdwroutine = GetFdwRoutineForRelation(target_relation, false);

		if (fdwroutine->AddForeignUpdateTargets != NULL)
			fdwroutine->AddForeignUpdateTargets(parsetree, target_rte,
												target_relation);

		/*
		 * If we have a row-level trigger corresponding to the operation, emit
		 * a whole-row Var so that executor will have the "old" row to pass to
		 * the trigger.  Alas, this misses system columns.
		 */
		if (target_relation->trigdesc &&
			((parsetree->commandType == CMD_UPDATE &&
			  (target_relation->trigdesc->trig_update_after_row ||
			   target_relation->trigdesc->trig_update_before_row)) ||
			 (parsetree->commandType == CMD_DELETE &&
			  (target_relation->trigdesc->trig_delete_after_row ||
			   target_relation->trigdesc->trig_delete_before_row))))
		{
			var = makeWholeRowVar(target_rte,
								  parsetree->resultRelation,
								  0,
								  false);

			attrname = "wholerow";
		}
	}

	if (var != NULL)
	{
		tle = makeTargetEntry((Expr *) var,
							  list_length(parsetree->targetList) + 1,
							  pstrdup(attrname),
							  true);

		parsetree->targetList = lappend(parsetree->targetList, tle);
	}
}