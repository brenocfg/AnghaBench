#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* reltarget; } ;
struct TYPE_6__ {int /*<<< orphan*/  per_tuple; int /*<<< orphan*/  startup; } ;
struct TYPE_7__ {int /*<<< orphan*/  width; TYPE_1__ cost; int /*<<< orphan*/ * exprs; } ;
typedef  TYPE_3__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  AppendRelInfo ;

/* Variables and functions */
 scalar_t__ adjust_appendrel_attrs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
build_child_join_reltarget(PlannerInfo *root,
						   RelOptInfo *parentrel,
						   RelOptInfo *childrel,
						   int nappinfos,
						   AppendRelInfo **appinfos)
{
	/* Build the targetlist */
	childrel->reltarget->exprs = (List *)
		adjust_appendrel_attrs(root,
							   (Node *) parentrel->reltarget->exprs,
							   nappinfos, appinfos);

	/* Set the cost and width fields */
	childrel->reltarget->cost.startup = parentrel->reltarget->cost.startup;
	childrel->reltarget->cost.per_tuple = parentrel->reltarget->cost.per_tuple;
	childrel->reltarget->width = parentrel->reltarget->width;
}