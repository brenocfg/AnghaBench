#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  commandType; } ;
struct TYPE_5__ {char const* sourceText; int instrument_options; int already_executed; int /*<<< orphan*/ * totaltime; int /*<<< orphan*/ * planstate; int /*<<< orphan*/ * estate; int /*<<< orphan*/ * tupDesc; int /*<<< orphan*/ * queryEnv; int /*<<< orphan*/  params; int /*<<< orphan*/ * dest; void* crosscheck_snapshot; void* snapshot; TYPE_2__* plannedstmt; int /*<<< orphan*/  operation; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  QueryEnvironment ;
typedef  TYPE_1__ QueryDesc ;
typedef  TYPE_2__ PlannedStmt ;
typedef  int /*<<< orphan*/  ParamListInfo ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 void* RegisterSnapshot (int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 

QueryDesc *
CreateQueryDesc(PlannedStmt *plannedstmt,
				const char *sourceText,
				Snapshot snapshot,
				Snapshot crosscheck_snapshot,
				DestReceiver *dest,
				ParamListInfo params,
				QueryEnvironment *queryEnv,
				int instrument_options)
{
	QueryDesc  *qd = (QueryDesc *) palloc(sizeof(QueryDesc));

	qd->operation = plannedstmt->commandType;	/* operation */
	qd->plannedstmt = plannedstmt;	/* plan */
	qd->sourceText = sourceText;	/* query text */
	qd->snapshot = RegisterSnapshot(snapshot);	/* snapshot */
	/* RI check snapshot */
	qd->crosscheck_snapshot = RegisterSnapshot(crosscheck_snapshot);
	qd->dest = dest;			/* output dest */
	qd->params = params;		/* parameter values passed into query */
	qd->queryEnv = queryEnv;
	qd->instrument_options = instrument_options;	/* instrumentation wanted? */

	/* null these fields until set by ExecutorStart */
	qd->tupDesc = NULL;
	qd->estate = NULL;
	qd->planstate = NULL;
	qd->totaltime = NULL;

	/* not yet executed */
	qd->already_executed = false;

	return qd;
}