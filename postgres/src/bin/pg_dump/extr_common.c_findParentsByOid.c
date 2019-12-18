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
struct TYPE_8__ {scalar_t__ oid; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; TYPE_1__ catId; } ;
struct TYPE_10__ {int numParents; struct TYPE_10__** parents; TYPE_2__ dobj; } ;
typedef  TYPE_3__ TableInfo ;
struct TYPE_11__ {scalar_t__ inhrelid; int /*<<< orphan*/  inhparent; } ;
typedef  scalar_t__ Oid ;
typedef  TYPE_4__ InhInfo ;

/* Variables and functions */
 int /*<<< orphan*/  exit_nicely (int) ; 
 TYPE_3__* findTableByOid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pg_malloc (int) ; 

__attribute__((used)) static void
findParentsByOid(TableInfo *self,
				 InhInfo *inhinfo, int numInherits)
{
	Oid			oid = self->dobj.catId.oid;
	int			i,
				j;
	int			numParents;

	numParents = 0;
	for (i = 0; i < numInherits; i++)
	{
		if (inhinfo[i].inhrelid == oid)
			numParents++;
	}

	self->numParents = numParents;

	if (numParents > 0)
	{
		self->parents = (TableInfo **)
			pg_malloc(sizeof(TableInfo *) * numParents);
		j = 0;
		for (i = 0; i < numInherits; i++)
		{
			if (inhinfo[i].inhrelid == oid)
			{
				TableInfo  *parent;

				parent = findTableByOid(inhinfo[i].inhparent);
				if (parent == NULL)
				{
					pg_log_error("failed sanity check, parent OID %u of table \"%s\" (OID %u) not found",
								 inhinfo[i].inhparent,
								 self->dobj.name,
								 oid);
					exit_nicely(1);
				}
				self->parents[j++] = parent;
			}
		}
	}
	else
		self->parents = NULL;
}