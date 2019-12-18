#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
struct TYPE_8__ {TYPE_6__* qd; scalar_t__ lazyEval; } ;
typedef  TYPE_2__ execution_state ;
struct TYPE_10__ {scalar_t__ operation; TYPE_1__* estate; int /*<<< orphan*/  dest; int /*<<< orphan*/  queryEnv; int /*<<< orphan*/  params; int /*<<< orphan*/  plannedstmt; } ;
struct TYPE_9__ {int /*<<< orphan*/  returnsSet; int /*<<< orphan*/  src; } ;
struct TYPE_7__ {scalar_t__ es_processed; } ;
typedef  TYPE_3__* SQLFunctionCachePtr ;

/* Variables and functions */
 scalar_t__ CMD_UTILITY ; 
 int /*<<< orphan*/  ExecutorRun (TYPE_6__*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  PROCESS_UTILITY_QUERY ; 
 int /*<<< orphan*/  ProcessUtility (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
postquel_getnext(execution_state *es, SQLFunctionCachePtr fcache)
{
	bool		result;

	if (es->qd->operation == CMD_UTILITY)
	{
		ProcessUtility(es->qd->plannedstmt,
					   fcache->src,
					   PROCESS_UTILITY_QUERY,
					   es->qd->params,
					   es->qd->queryEnv,
					   es->qd->dest,
					   NULL);
		result = true;			/* never stops early */
	}
	else
	{
		/* Run regular commands to completion unless lazyEval */
		uint64		count = (es->lazyEval) ? 1 : 0;

		ExecutorRun(es->qd, ForwardScanDirection, count, !fcache->returnsSet || !es->lazyEval);

		/*
		 * If we requested run to completion OR there was no tuple returned,
		 * command must be complete.
		 */
		result = (count == 0 || es->qd->estate->es_processed == 0);
	}

	return result;
}