#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct xa_state {int xa_offset; TYPE_1__* xa_node; int /*<<< orphan*/  xa; int /*<<< orphan*/  xa_index; } ;
struct TYPE_8__ {int offset; } ;

/* Variables and functions */
 int get_offset (int /*<<< orphan*/ ,TYPE_1__*) ; 
 void* set_bounds (struct xa_state*) ; 
 void* xa_entry (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  xa_is_node (void*) ; 
 TYPE_1__* xa_parent (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* xa_to_node (void*) ; 
 int /*<<< orphan*/  xas_frozen (TYPE_1__*) ; 
 void* xas_load (struct xa_state*) ; 
 scalar_t__ xas_not_node (TYPE_1__*) ; 
 int /*<<< orphan*/  xas_set_offset (struct xa_state*) ; 

void *__xas_prev(struct xa_state *xas)
{
	void *entry;

	if (!xas_frozen(xas->xa_node))
		xas->xa_index--;
	if (!xas->xa_node)
		return set_bounds(xas);
	if (xas_not_node(xas->xa_node))
		return xas_load(xas);

	if (xas->xa_offset != get_offset(xas->xa_index, xas->xa_node))
		xas->xa_offset--;

	while (xas->xa_offset == 255) {
		xas->xa_offset = xas->xa_node->offset - 1;
		xas->xa_node = xa_parent(xas->xa, xas->xa_node);
		if (!xas->xa_node)
			return set_bounds(xas);
	}

	for (;;) {
		entry = xa_entry(xas->xa, xas->xa_node, xas->xa_offset);
		if (!xa_is_node(entry))
			return entry;

		xas->xa_node = xa_to_node(entry);
		xas_set_offset(xas);
	}
}