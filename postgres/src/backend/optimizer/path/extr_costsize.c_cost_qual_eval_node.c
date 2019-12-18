#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ per_tuple; scalar_t__ startup; } ;
struct TYPE_5__ {TYPE_2__ total; int /*<<< orphan*/ * root; } ;
typedef  TYPE_1__ cost_qual_eval_context ;
typedef  TYPE_2__ QualCost ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  cost_qual_eval_walker (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
cost_qual_eval_node(QualCost *cost, Node *qual, PlannerInfo *root)
{
	cost_qual_eval_context context;

	context.root = root;
	context.total.startup = 0;
	context.total.per_tuple = 0;

	cost_qual_eval_walker(qual, &context);

	*cost = context.total;
}