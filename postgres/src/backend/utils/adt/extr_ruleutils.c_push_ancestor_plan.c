#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ancestors; } ;
typedef  TYPE_1__ deparse_namespace ;
typedef  int /*<<< orphan*/  PlanState ;
typedef  int /*<<< orphan*/  ListCell ;

/* Variables and functions */
 scalar_t__ lfirst (int /*<<< orphan*/ *) ; 
 scalar_t__ list_cell_number (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_copy_tail (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_deparse_planstate (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
push_ancestor_plan(deparse_namespace *dpns, ListCell *ancestor_cell,
				   deparse_namespace *save_dpns)
{
	PlanState  *ps = (PlanState *) lfirst(ancestor_cell);

	/* Save state for restoration later */
	*save_dpns = *dpns;

	/* Build a new ancestor list with just this node's ancestors */
	dpns->ancestors =
		list_copy_tail(dpns->ancestors,
					   list_cell_number(dpns->ancestors, ancestor_cell) + 1);

	/* Set attention on selected ancestor */
	set_deparse_planstate(dpns, ps);
}