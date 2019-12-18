#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ relkind; int postponed_def; } ;
typedef  TYPE_1__ TableInfo ;
struct TYPE_7__ {scalar_t__ objType; int /*<<< orphan*/  dumpId; } ;
typedef  TYPE_2__ DumpableObject ;

/* Variables and functions */
 scalar_t__ DO_TABLE ; 
 scalar_t__ RELKIND_MATVIEW ; 
 int /*<<< orphan*/  removeObjectDependency (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
repairMatViewBoundaryMultiLoop(DumpableObject *boundaryobj,
							   DumpableObject *nextobj)
{
	/* remove boundary's dependency on object after it in loop */
	removeObjectDependency(boundaryobj, nextobj->dumpId);
	/* if that object is a matview, mark it as postponed into post-data */
	if (nextobj->objType == DO_TABLE)
	{
		TableInfo  *nextinfo = (TableInfo *) nextobj;

		if (nextinfo->relkind == RELKIND_MATVIEW)
			nextinfo->postponed_def = true;
	}
}