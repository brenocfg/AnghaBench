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
struct TYPE_5__ {int dump; } ;
struct TYPE_6__ {char relkind; TYPE_1__ dobj; } ;
typedef  TYPE_2__ TableInfo ;
typedef  int /*<<< orphan*/  DumpOptions ;

/* Variables and functions */
 int DUMP_COMPONENT_DATA ; 
 int /*<<< orphan*/  makeTableDataInfo (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void
getTableData(DumpOptions *dopt, TableInfo *tblinfo, int numTables, char relkind)
{
	int			i;

	for (i = 0; i < numTables; i++)
	{
		if (tblinfo[i].dobj.dump & DUMP_COMPONENT_DATA &&
			(!relkind || tblinfo[i].relkind == relkind))
			makeTableDataInfo(dopt, &(tblinfo[i]));
	}
}