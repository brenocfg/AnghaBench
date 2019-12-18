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
struct xa_state {scalar_t__ xa_shift; } ;
struct xa_node {scalar_t__ shift; } ;

/* Variables and functions */
 scalar_t__ xa_is_node (void*) ; 
 struct xa_node* xa_to_node (void*) ; 
 void* xas_descend (struct xa_state*,struct xa_node*) ; 
 void* xas_start (struct xa_state*) ; 

void *xas_load(struct xa_state *xas)
{
	void *entry = xas_start(xas);

	while (xa_is_node(entry)) {
		struct xa_node *node = xa_to_node(entry);

		if (xas->xa_shift > node->shift)
			break;
		entry = xas_descend(xas, node);
		if (node->shift == 0)
			break;
	}
	return entry;
}