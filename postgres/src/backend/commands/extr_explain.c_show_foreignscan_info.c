#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  (* ExplainForeignScan ) (TYPE_3__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* ExplainDirectModify ) (TYPE_3__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_12__ {scalar_t__ operation; } ;
struct TYPE_9__ {scalar_t__ plan; } ;
struct TYPE_10__ {TYPE_1__ ps; } ;
struct TYPE_11__ {TYPE_2__ ss; TYPE_5__* fdwroutine; } ;
typedef  TYPE_3__ ForeignScanState ;
typedef  TYPE_4__ ForeignScan ;
typedef  TYPE_5__ FdwRoutine ;
typedef  int /*<<< orphan*/  ExplainState ;

/* Variables and functions */
 scalar_t__ CMD_SELECT ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
show_foreignscan_info(ForeignScanState *fsstate, ExplainState *es)
{
	FdwRoutine *fdwroutine = fsstate->fdwroutine;

	/* Let the FDW emit whatever fields it wants */
	if (((ForeignScan *) fsstate->ss.ps.plan)->operation != CMD_SELECT)
	{
		if (fdwroutine->ExplainDirectModify != NULL)
			fdwroutine->ExplainDirectModify(fsstate, es);
	}
	else
	{
		if (fdwroutine->ExplainForeignScan != NULL)
			fdwroutine->ExplainForeignScan(fsstate, es);
	}
}