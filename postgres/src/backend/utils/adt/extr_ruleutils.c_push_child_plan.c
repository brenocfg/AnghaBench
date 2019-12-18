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
struct TYPE_5__ {int /*<<< orphan*/  ancestors; int /*<<< orphan*/  planstate; } ;
typedef  TYPE_1__ deparse_namespace ;
typedef  int /*<<< orphan*/  PlanState ;

/* Variables and functions */
 int /*<<< orphan*/  lcons (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_deparse_planstate (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
push_child_plan(deparse_namespace *dpns, PlanState *ps,
				deparse_namespace *save_dpns)
{
	/* Save state for restoration later */
	*save_dpns = *dpns;

	/* Link current plan node into ancestors list */
	dpns->ancestors = lcons(dpns->planstate, dpns->ancestors);

	/* Set attention on selected child */
	set_deparse_planstate(dpns, ps);
}