#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xa_mark_t ;
struct xa_state {unsigned int xa_offset; int /*<<< orphan*/  xa; struct xa_node* xa_node; } ;
struct xa_node {unsigned int offset; } ;

/* Variables and functions */
 scalar_t__ node_set_mark (struct xa_node*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_mark_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_marked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xa_node* xa_parent_locked (int /*<<< orphan*/ ,struct xa_node*) ; 
 scalar_t__ xas_invalid (struct xa_state const*) ; 

void xas_set_mark(const struct xa_state *xas, xa_mark_t mark)
{
	struct xa_node *node = xas->xa_node;
	unsigned int offset = xas->xa_offset;

	if (xas_invalid(xas))
		return;

	while (node) {
		if (node_set_mark(node, offset, mark))
			return;
		offset = node->offset;
		node = xa_parent_locked(xas->xa, node);
	}

	if (!xa_marked(xas->xa, mark))
		xa_mark_set(xas->xa, mark);
}