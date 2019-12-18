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
struct genradix_root {int dummy; } ;
struct genradix_node {void* data; struct genradix_node** children; } ;
struct __genradix {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 struct genradix_root* READ_ONCE (int /*<<< orphan*/ ) ; 
 size_t genradix_depth_shift (unsigned int) ; 
 int genradix_depth_size (unsigned int) ; 
 unsigned int genradix_root_to_depth (struct genradix_root*) ; 
 struct genradix_node* genradix_root_to_node (struct genradix_root*) ; 
 size_t ilog2 (size_t) ; 

void *__genradix_ptr(struct __genradix *radix, size_t offset)
{
	struct genradix_root *r = READ_ONCE(radix->root);
	struct genradix_node *n = genradix_root_to_node(r);
	unsigned level		= genradix_root_to_depth(r);

	if (ilog2(offset) >= genradix_depth_shift(level))
		return NULL;

	while (1) {
		if (!n)
			return NULL;
		if (!level)
			break;

		level--;

		n = n->children[offset >> genradix_depth_shift(level)];
		offset &= genradix_depth_size(level) - 1;
	}

	return &n->data[offset];
}