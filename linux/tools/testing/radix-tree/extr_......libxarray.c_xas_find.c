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
struct xa_state {int xa_index; int xa_offset; TYPE_1__* xa_node; int /*<<< orphan*/  xa; } ;
struct TYPE_8__ {scalar_t__ offset; int /*<<< orphan*/  shift; } ;

/* Variables and functions */
 TYPE_1__* XAS_BOUNDS ; 
 int XA_CHUNK_MASK ; 
 scalar_t__ XA_CHUNK_SIZE ; 
 void* set_bounds (struct xa_state*) ; 
 scalar_t__ unlikely (int) ; 
 void* xa_entry (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 scalar_t__ xa_is_node (void*) ; 
 int /*<<< orphan*/  xa_is_sibling (void*) ; 
 TYPE_1__* xa_parent (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* xa_to_node (void*) ; 
 int /*<<< orphan*/  xas_advance (struct xa_state*) ; 
 scalar_t__ xas_error (struct xa_state*) ; 
 void* xas_load (struct xa_state*) ; 
 scalar_t__ xas_not_node (TYPE_1__*) ; 
 scalar_t__ xas_top (TYPE_1__*) ; 

void *xas_find(struct xa_state *xas, unsigned long max)
{
	void *entry;

	if (xas_error(xas))
		return NULL;

	if (!xas->xa_node) {
		xas->xa_index = 1;
		return set_bounds(xas);
	} else if (xas_top(xas->xa_node)) {
		entry = xas_load(xas);
		if (entry || xas_not_node(xas->xa_node))
			return entry;
	} else if (!xas->xa_node->shift &&
		    xas->xa_offset != (xas->xa_index & XA_CHUNK_MASK)) {
		xas->xa_offset = ((xas->xa_index - 1) & XA_CHUNK_MASK) + 1;
	}

	xas_advance(xas);

	while (xas->xa_node && (xas->xa_index <= max)) {
		if (unlikely(xas->xa_offset == XA_CHUNK_SIZE)) {
			xas->xa_offset = xas->xa_node->offset + 1;
			xas->xa_node = xa_parent(xas->xa, xas->xa_node);
			continue;
		}

		entry = xa_entry(xas->xa, xas->xa_node, xas->xa_offset);
		if (xa_is_node(entry)) {
			xas->xa_node = xa_to_node(entry);
			xas->xa_offset = 0;
			continue;
		}
		if (entry && !xa_is_sibling(entry))
			return entry;

		xas_advance(xas);
	}

	if (!xas->xa_node)
		xas->xa_node = XAS_BOUNDS;
	return NULL;
}