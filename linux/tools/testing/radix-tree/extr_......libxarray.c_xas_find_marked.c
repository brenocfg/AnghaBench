#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xa_mark_t ;
struct xa_state {int xa_index; int xa_offset; TYPE_1__* xa_node; int /*<<< orphan*/  xa; } ;
struct TYPE_6__ {int shift; unsigned int offset; } ;

/* Variables and functions */
 TYPE_1__* XAS_RESTART ; 
 unsigned int XA_CHUNK_SIZE ; 
 scalar_t__ max_index (void*) ; 
 void* set_bounds (struct xa_state*) ; 
 scalar_t__ unlikely (int) ; 
 void* xa_entry (int /*<<< orphan*/ ,TYPE_1__*,unsigned int) ; 
 void* xa_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_is_node (void*) ; 
 scalar_t__ xa_is_sibling (void*) ; 
 scalar_t__ xa_marked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* xa_parent (int /*<<< orphan*/ ,TYPE_1__*) ; 
 void* xa_to_node (void*) ; 
 unsigned int xa_to_sibling (void*) ; 
 scalar_t__ xas_error (struct xa_state*) ; 
 unsigned int xas_find_chunk (struct xa_state*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas_move_index (struct xa_state*,unsigned int) ; 
 int /*<<< orphan*/  xas_set_offset (struct xa_state*) ; 
 scalar_t__ xas_top (TYPE_1__*) ; 

void *xas_find_marked(struct xa_state *xas, unsigned long max, xa_mark_t mark)
{
	bool advance = true;
	unsigned int offset;
	void *entry;

	if (xas_error(xas))
		return NULL;

	if (!xas->xa_node) {
		xas->xa_index = 1;
		goto out;
	} else if (xas_top(xas->xa_node)) {
		advance = false;
		entry = xa_head(xas->xa);
		xas->xa_node = NULL;
		if (xas->xa_index > max_index(entry))
			goto out;
		if (!xa_is_node(entry)) {
			if (xa_marked(xas->xa, mark))
				return entry;
			xas->xa_index = 1;
			goto out;
		}
		xas->xa_node = xa_to_node(entry);
		xas->xa_offset = xas->xa_index >> xas->xa_node->shift;
	}

	while (xas->xa_index <= max) {
		if (unlikely(xas->xa_offset == XA_CHUNK_SIZE)) {
			xas->xa_offset = xas->xa_node->offset + 1;
			xas->xa_node = xa_parent(xas->xa, xas->xa_node);
			if (!xas->xa_node)
				break;
			advance = false;
			continue;
		}

		if (!advance) {
			entry = xa_entry(xas->xa, xas->xa_node, xas->xa_offset);
			if (xa_is_sibling(entry)) {
				xas->xa_offset = xa_to_sibling(entry);
				xas_move_index(xas, xas->xa_offset);
			}
		}

		offset = xas_find_chunk(xas, advance, mark);
		if (offset > xas->xa_offset) {
			advance = false;
			xas_move_index(xas, offset);
			/* Mind the wrap */
			if ((xas->xa_index - 1) >= max)
				goto max;
			xas->xa_offset = offset;
			if (offset == XA_CHUNK_SIZE)
				continue;
		}

		entry = xa_entry(xas->xa, xas->xa_node, xas->xa_offset);
		if (!xa_is_node(entry))
			return entry;
		xas->xa_node = xa_to_node(entry);
		xas_set_offset(xas);
	}

out:
	if (xas->xa_index > max)
		goto max;
	return set_bounds(xas);
max:
	xas->xa_node = XAS_RESTART;
	return NULL;
}