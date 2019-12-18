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
struct genradix_iter {int offset; size_t pos; } ;
struct __genradix {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int GENRADIX_ARY ; 
 size_t PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 struct genradix_root* READ_ONCE (int /*<<< orphan*/ ) ; 
 int genradix_depth_shift (unsigned int) ; 
 scalar_t__ genradix_depth_size (unsigned int) ; 
 unsigned int genradix_root_to_depth (struct genradix_root*) ; 
 struct genradix_node* genradix_root_to_node (struct genradix_root*) ; 
 int ilog2 (int) ; 
 int round_down (scalar_t__,scalar_t__) ; 

void *__genradix_iter_peek(struct genradix_iter *iter,
			   struct __genradix *radix,
			   size_t objs_per_page)
{
	struct genradix_root *r;
	struct genradix_node *n;
	unsigned level, i;
restart:
	r = READ_ONCE(radix->root);
	if (!r)
		return NULL;

	n	= genradix_root_to_node(r);
	level	= genradix_root_to_depth(r);

	if (ilog2(iter->offset) >= genradix_depth_shift(level))
		return NULL;

	while (level) {
		level--;

		i = (iter->offset >> genradix_depth_shift(level)) &
			(GENRADIX_ARY - 1);

		while (!n->children[i]) {
			i++;
			iter->offset = round_down(iter->offset +
					   genradix_depth_size(level),
					   genradix_depth_size(level));
			iter->pos = (iter->offset >> PAGE_SHIFT) *
				objs_per_page;
			if (i == GENRADIX_ARY)
				goto restart;
		}

		n = n->children[i];
	}

	return &n->data[iter->offset & (PAGE_SIZE - 1)];
}