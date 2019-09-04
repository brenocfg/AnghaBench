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
struct TYPE_3__ {scalar_t__ pre_visit; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ RTreeVisitor ;
typedef  scalar_t__ RTreeNodeVisitCb ;
typedef  int /*<<< orphan*/  RTree ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_tree_dfs (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ trace_traverse_pre ; 

__attribute__((used)) static void trace_traverse (RTree *t) {
	RTreeVisitor vis = { 0 };

	/* clear the line on stderr, because somebody has written there */
	fprintf (stderr, "\x1b[2K\r");
	fflush (stderr);
	vis.pre_visit = (RTreeNodeVisitCb)trace_traverse_pre;
	r_tree_dfs (t, &vis);
}