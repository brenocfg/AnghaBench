#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_4__* dataObj; } ;
typedef  TYPE_5__ TableInfo ;
struct TYPE_17__ {TYPE_2__* contable; int /*<<< orphan*/  confrelid; } ;
struct TYPE_16__ {scalar_t__ objType; } ;
struct TYPE_13__ {int /*<<< orphan*/  dumpId; } ;
struct TYPE_14__ {TYPE_3__ dobj; } ;
struct TYPE_12__ {TYPE_1__* dataObj; } ;
struct TYPE_11__ {int /*<<< orphan*/  dobj; } ;
typedef  TYPE_6__ DumpableObject ;
typedef  TYPE_7__ ConstraintInfo ;

/* Variables and functions */
 scalar_t__ DO_FK_CONSTRAINT ; 
 int /*<<< orphan*/  addObjectDependency (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* findTableByOid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_6__**) ; 
 int /*<<< orphan*/  getDumpableObjects (TYPE_6__***,int*) ; 

__attribute__((used)) static void
getTableDataFKConstraints(void)
{
	DumpableObject **dobjs;
	int			numObjs;
	int			i;

	/* Search through all the dumpable objects for FK constraints */
	getDumpableObjects(&dobjs, &numObjs);
	for (i = 0; i < numObjs; i++)
	{
		if (dobjs[i]->objType == DO_FK_CONSTRAINT)
		{
			ConstraintInfo *cinfo = (ConstraintInfo *) dobjs[i];
			TableInfo  *ftable;

			/* Not interesting unless both tables are to be dumped */
			if (cinfo->contable == NULL ||
				cinfo->contable->dataObj == NULL)
				continue;
			ftable = findTableByOid(cinfo->confrelid);
			if (ftable == NULL ||
				ftable->dataObj == NULL)
				continue;

			/*
			 * Okay, make referencing table's TABLE_DATA object depend on the
			 * referenced table's TABLE_DATA object.
			 */
			addObjectDependency(&cinfo->contable->dataObj->dobj,
								ftable->dataObj->dobj.dumpId);
		}
	}
	free(dobjs);
}