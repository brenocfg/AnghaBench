#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ancestors; } ;
typedef  TYPE_1__ deparse_namespace ;
typedef  int /*<<< orphan*/  PlanState ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_deparse_planstate (TYPE_1__*,int /*<<< orphan*/ *) ; 

List *
set_deparse_context_planstate(List *dpcontext,
							  Node *planstate, List *ancestors)
{
	deparse_namespace *dpns;

	/* Should always have one-entry namespace list for Plan deparsing */
	Assert(list_length(dpcontext) == 1);
	dpns = (deparse_namespace *) linitial(dpcontext);

	/* Set our attention on the specific plan node passed in */
	set_deparse_planstate(dpns, (PlanState *) planstate);
	dpns->ancestors = ancestors;

	return dpcontext;
}