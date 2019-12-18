#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ query_depth; scalar_t__ maxquerydepth; } ;
struct TYPE_4__ {int before_trig_done; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  CmdType ;
typedef  TYPE_1__ AfterTriggersTableData ;

/* Variables and functions */
 int /*<<< orphan*/  AfterTriggerEnlargeQueryState () ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_1__* GetAfterTriggersTableData (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ afterTriggers ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
before_stmt_triggers_fired(Oid relid, CmdType cmdType)
{
	bool		result;
	AfterTriggersTableData *table;

	/* Check state, like AfterTriggerSaveEvent. */
	if (afterTriggers.query_depth < 0)
		elog(ERROR, "before_stmt_triggers_fired() called outside of query");

	/* Be sure we have enough space to record events at this query depth. */
	if (afterTriggers.query_depth >= afterTriggers.maxquerydepth)
		AfterTriggerEnlargeQueryState();

	/*
	 * We keep this state in the AfterTriggersTableData that also holds
	 * transition tables for the relation + operation.  In this way, if we are
	 * forced to make a new set of transition tables because more tuples get
	 * entered after we've already fired triggers, we will allow a new set of
	 * statement triggers to get queued.
	 */
	table = GetAfterTriggersTableData(relid, cmdType);
	result = table->before_trig_done;
	table->before_trig_done = true;
	return result;
}