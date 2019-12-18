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
struct TYPE_13__ {scalar_t__ verbose; } ;
struct TYPE_12__ {int /*<<< orphan*/ * fdw_private; } ;
struct TYPE_9__ {scalar_t__ plan; } ;
struct TYPE_10__ {TYPE_1__ ps; } ;
struct TYPE_11__ {TYPE_2__ ss; } ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_3__ ForeignScanState ;
typedef  TYPE_4__ ForeignScan ;
typedef  TYPE_5__ ExplainState ;

/* Variables and functions */
 int /*<<< orphan*/  ExplainPropertyText (char*,char*,TYPE_5__*) ; 
 scalar_t__ FdwScanPrivateRelations ; 
 scalar_t__ FdwScanPrivateSelectSql ; 
 scalar_t__ list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_nth (int /*<<< orphan*/ *,scalar_t__) ; 
 char* strVal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
postgresExplainForeignScan(ForeignScanState *node, ExplainState *es)
{
	List	   *fdw_private;
	char	   *sql;
	char	   *relations;

	fdw_private = ((ForeignScan *) node->ss.ps.plan)->fdw_private;

	/*
	 * Add names of relation handled by the foreign scan when the scan is a
	 * join
	 */
	if (list_length(fdw_private) > FdwScanPrivateRelations)
	{
		relations = strVal(list_nth(fdw_private, FdwScanPrivateRelations));
		ExplainPropertyText("Relations", relations, es);
	}

	/*
	 * Add remote query, when VERBOSE option is specified.
	 */
	if (es->verbose)
	{
		sql = strVal(list_nth(fdw_private, FdwScanPrivateSelectSql));
		ExplainPropertyText("Remote SQL", sql, es);
	}
}