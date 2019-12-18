#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  next; int /*<<< orphan*/  prev; } ;
struct xa_node {int /*<<< orphan*/ ** marks; TYPE_1__ private_list; int /*<<< orphan*/  array; int /*<<< orphan*/  nr_values; int /*<<< orphan*/  count; int /*<<< orphan*/  shift; scalar_t__ parent; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 unsigned int XA_MARK_LONGS ; 
 unsigned int XA_MAX_MARKS ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 

void xa_dump_node(const struct xa_node *node)
{
	unsigned i, j;

	if (!node)
		return;
	if ((unsigned long)node & 3) {
		pr_cont("node %px\n", node);
		return;
	}

	pr_cont("node %px %s %d parent %px shift %d count %d values %d "
		"array %px list %px %px marks",
		node, node->parent ? "offset" : "max", node->offset,
		node->parent, node->shift, node->count, node->nr_values,
		node->array, node->private_list.prev, node->private_list.next);
	for (i = 0; i < XA_MAX_MARKS; i++)
		for (j = 0; j < XA_MARK_LONGS; j++)
			pr_cont(" %lx", node->marks[i][j]);
	pr_cont("\n");
}