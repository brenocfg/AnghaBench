#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* shellType; } ;
typedef  TYPE_3__ TypeInfo ;
struct TYPE_12__ {int dump; int /*<<< orphan*/  dumpId; } ;
struct TYPE_9__ {int dump; int /*<<< orphan*/  dumpId; } ;
struct TYPE_10__ {TYPE_1__ dobj; } ;
typedef  TYPE_4__ DumpableObject ;

/* Variables and functions */
 int DUMP_COMPONENT_DEFINITION ; 
 int /*<<< orphan*/  addObjectDependency (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  removeObjectDependency (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
repairTypeFuncLoop(DumpableObject *typeobj, DumpableObject *funcobj)
{
	TypeInfo   *typeInfo = (TypeInfo *) typeobj;

	/* remove function's dependency on type */
	removeObjectDependency(funcobj, typeobj->dumpId);

	/* add function's dependency on shell type, instead */
	if (typeInfo->shellType)
	{
		addObjectDependency(funcobj, typeInfo->shellType->dobj.dumpId);

		/*
		 * Mark shell type (always including the definition, as we need the
		 * shell type defined to identify the function fully) as to be dumped
		 * if any such function is
		 */
		if (funcobj->dump)
			typeInfo->shellType->dobj.dump = funcobj->dump |
				DUMP_COMPONENT_DEFINITION;
	}
}