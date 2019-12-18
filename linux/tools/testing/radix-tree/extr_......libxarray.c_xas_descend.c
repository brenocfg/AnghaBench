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
struct xa_state {unsigned int xa_offset; int /*<<< orphan*/  xa; struct xa_node* xa_node; int /*<<< orphan*/  xa_index; } ;
struct xa_node {int dummy; } ;

/* Variables and functions */
 unsigned int get_offset (int /*<<< orphan*/ ,struct xa_node*) ; 
 void* xa_entry (int /*<<< orphan*/ ,struct xa_node*,unsigned int) ; 
 scalar_t__ xa_is_sibling (void*) ; 
 unsigned int xa_to_sibling (void*) ; 

__attribute__((used)) static void *xas_descend(struct xa_state *xas, struct xa_node *node)
{
	unsigned int offset = get_offset(xas->xa_index, node);
	void *entry = xa_entry(xas->xa, node, offset);

	xas->xa_node = node;
	if (xa_is_sibling(entry)) {
		offset = xa_to_sibling(entry);
		entry = xa_entry(xas->xa, node, offset);
	}

	xas->xa_offset = offset;
	return entry;
}