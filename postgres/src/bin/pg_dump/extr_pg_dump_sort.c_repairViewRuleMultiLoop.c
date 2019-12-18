#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int dummy_view; } ;
typedef  TYPE_1__ TableInfo ;
struct TYPE_10__ {int /*<<< orphan*/  dumpId; } ;
struct TYPE_9__ {int separate; } ;
typedef  TYPE_2__ RuleInfo ;
typedef  TYPE_3__ DumpableObject ;

/* Variables and functions */
 int /*<<< orphan*/  addObjectDependency (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  postDataBoundId ; 
 int /*<<< orphan*/  removeObjectDependency (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
repairViewRuleMultiLoop(DumpableObject *viewobj,
						DumpableObject *ruleobj)
{
	TableInfo  *viewinfo = (TableInfo *) viewobj;
	RuleInfo   *ruleinfo = (RuleInfo *) ruleobj;

	/* remove view's dependency on rule */
	removeObjectDependency(viewobj, ruleobj->dumpId);
	/* mark view to be printed with a dummy definition */
	viewinfo->dummy_view = true;
	/* mark rule as needing its own dump */
	ruleinfo->separate = true;
	/* put back rule's dependency on view */
	addObjectDependency(ruleobj, viewobj->dumpId);
	/* now that rule is separate, it must be post-data */
	addObjectDependency(ruleobj, postDataBoundId);
}