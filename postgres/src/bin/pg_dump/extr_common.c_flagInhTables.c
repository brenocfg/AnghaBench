#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dump; } ;
struct TYPE_9__ {scalar_t__ relkind; int numParents; int interesting; struct TYPE_9__** parents; int /*<<< orphan*/  ispartition; TYPE_1__ dobj; } ;
typedef  TYPE_2__ TableInfo ;
struct TYPE_11__ {TYPE_3__* dopt; } ;
struct TYPE_10__ {int /*<<< orphan*/  load_via_partition_root; } ;
typedef  int /*<<< orphan*/  InhInfo ;
typedef  TYPE_3__ DumpOptions ;
typedef  TYPE_4__ Archive ;

/* Variables and functions */
 scalar_t__ RELKIND_MATVIEW ; 
 scalar_t__ RELKIND_SEQUENCE ; 
 scalar_t__ RELKIND_VIEW ; 
 int /*<<< orphan*/  findParentsByOid (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
flagInhTables(Archive *fout, TableInfo *tblinfo, int numTables,
			  InhInfo *inhinfo, int numInherits)
{
	DumpOptions *dopt = fout->dopt;
	int			i,
				j;

	for (i = 0; i < numTables; i++)
	{
		bool		find_parents = true;
		bool		mark_parents = true;

		/* Some kinds never have parents */
		if (tblinfo[i].relkind == RELKIND_SEQUENCE ||
			tblinfo[i].relkind == RELKIND_VIEW ||
			tblinfo[i].relkind == RELKIND_MATVIEW)
			continue;

		/*
		 * Normally, we don't bother computing anything for non-target tables,
		 * but if load-via-partition-root is specified, we gather information
		 * on every partition in the system so that getRootTableInfo can trace
		 * from any given to leaf partition all the way up to the root.  (We
		 * don't need to mark them as interesting for getTableAttrs, though.)
		 */
		if (!tblinfo[i].dobj.dump)
		{
			mark_parents = false;

			if (!dopt->load_via_partition_root ||
				!tblinfo[i].ispartition)
				find_parents = false;
		}

		/* If needed, find all the immediate parent tables. */
		if (find_parents)
			findParentsByOid(&tblinfo[i], inhinfo, numInherits);

		/*
		 * If needed, mark the parents as interesting for getTableAttrs and
		 * getIndexes.
		 */
		if (mark_parents)
		{
			int			numParents = tblinfo[i].numParents;
			TableInfo **parents = tblinfo[i].parents;

			for (j = 0; j < numParents; j++)
				parents[j]->interesting = true;
		}
	}
}