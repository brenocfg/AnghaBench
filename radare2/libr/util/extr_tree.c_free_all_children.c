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
struct TYPE_3__ {scalar_t__ post_visit; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ RTreeVisitor ;
typedef  scalar_t__ RTreeNodeVisitCb ;
typedef  int /*<<< orphan*/  RTree ;

/* Variables and functions */
 scalar_t__ node_free ; 
 int /*<<< orphan*/  r_tree_bfs (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void free_all_children (RTree *t) {
	RTreeVisitor vis = { 0 };
	vis.post_visit = (RTreeNodeVisitCb)node_free;
	r_tree_bfs (t, &vis);
}