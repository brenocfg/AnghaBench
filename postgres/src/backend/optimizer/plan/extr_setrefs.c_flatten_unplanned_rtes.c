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
struct TYPE_3__ {int /*<<< orphan*/  subquery; } ;
typedef  TYPE_1__ RangeTblEntry ;
typedef  int /*<<< orphan*/  PlannerGlobal ;

/* Variables and functions */
 int /*<<< orphan*/  QTW_EXAMINE_RTES_BEFORE ; 
 int /*<<< orphan*/  flatten_rtes_walker ; 
 int /*<<< orphan*/  query_tree_walker (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
flatten_unplanned_rtes(PlannerGlobal *glob, RangeTblEntry *rte)
{
	/* Use query_tree_walker to find all RTEs in the parse tree */
	(void) query_tree_walker(rte->subquery,
							 flatten_rtes_walker,
							 (void *) glob,
							 QTW_EXAMINE_RTES_BEFORE);
}