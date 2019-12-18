#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  all_neighbours; int /*<<< orphan*/  in_nodes; int /*<<< orphan*/  out_nodes; int /*<<< orphan*/  data; int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ RGraphNode ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r_graph_node_free (RGraphNode *n) {
	if (!n) {
		return;
	}
	if (n->free) {
		n->free (n->data);
	}
	r_list_free (n->out_nodes);
	r_list_free (n->in_nodes);
	r_list_free (n->all_neighbours);
	free (n);
}