#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int separate; } ;
struct TYPE_7__ {int /*<<< orphan*/  dumpId; } ;
typedef  TYPE_1__ DumpableObject ;
typedef  TYPE_2__ ConstraintInfo ;

/* Variables and functions */
 int /*<<< orphan*/  addObjectDependency (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  postDataBoundId ; 
 int /*<<< orphan*/  removeObjectDependency (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
repairDomainConstraintMultiLoop(DumpableObject *domainobj,
								DumpableObject *constraintobj)
{
	/* remove domain's dependency on constraint */
	removeObjectDependency(domainobj, constraintobj->dumpId);
	/* mark constraint as needing its own dump */
	((ConstraintInfo *) constraintobj)->separate = true;
	/* put back constraint's dependency on domain */
	addObjectDependency(constraintobj, domainobj->dumpId);
	/* now that constraint is separate, it must be post-data */
	addObjectDependency(constraintobj, postDataBoundId);
}