#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int dump; } ;
struct TYPE_8__ {scalar_t__ relkind; int numParents; int ncheck; TYPE_4__* checkexprs; struct TYPE_8__** parents; TYPE_1__ dobj; } ;
typedef  TYPE_3__ TableInfo ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int conislocal; TYPE_2__ dobj; } ;
typedef  TYPE_4__ ConstraintInfo ;

/* Variables and functions */
 int DUMP_COMPONENT_DEFINITION ; 
 scalar_t__ RELKIND_SEQUENCE ; 
 scalar_t__ RELKIND_VIEW ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
guessConstraintInheritance(TableInfo *tblinfo, int numTables)
{
	int			i,
				j,
				k;

	for (i = 0; i < numTables; i++)
	{
		TableInfo  *tbinfo = &(tblinfo[i]);
		int			numParents;
		TableInfo **parents;
		TableInfo  *parent;

		/* Sequences and views never have parents */
		if (tbinfo->relkind == RELKIND_SEQUENCE ||
			tbinfo->relkind == RELKIND_VIEW)
			continue;

		/* Don't bother computing anything for non-target tables, either */
		if (!(tbinfo->dobj.dump & DUMP_COMPONENT_DEFINITION))
			continue;

		numParents = tbinfo->numParents;
		parents = tbinfo->parents;

		if (numParents == 0)
			continue;			/* nothing to see here, move along */

		/* scan for inherited CHECK constraints */
		for (j = 0; j < tbinfo->ncheck; j++)
		{
			ConstraintInfo *constr;

			constr = &(tbinfo->checkexprs[j]);

			for (k = 0; k < numParents; k++)
			{
				int			l;

				parent = parents[k];
				for (l = 0; l < parent->ncheck; l++)
				{
					ConstraintInfo *pconstr = &(parent->checkexprs[l]);

					if (strcmp(pconstr->dobj.name, constr->dobj.name) == 0)
					{
						constr->conislocal = false;
						break;
					}
				}
				if (!constr->conislocal)
					break;
			}
		}
	}
}