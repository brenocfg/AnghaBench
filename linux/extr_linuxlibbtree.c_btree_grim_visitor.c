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
struct btree_head {int /*<<< orphan*/  height; scalar_t__ node; } ;
struct btree_geo {int dummy; } ;

/* Variables and functions */
 size_t __btree_for_each (struct btree_head*,struct btree_geo*,scalar_t__,unsigned long,void (*) (void*,unsigned long,unsigned long*,size_t,void*),void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __btree_init (struct btree_head*) ; 
 void empty (void*,unsigned long,unsigned long*,size_t,void*) ; 

size_t btree_grim_visitor(struct btree_head *head, struct btree_geo *geo,
			  unsigned long opaque,
			  void (*func)(void *elem, unsigned long opaque,
				       unsigned long *key,
				       size_t index, void *func2),
			  void *func2)
{
	size_t count = 0;

	if (!func2)
		func = empty;
	if (head->node)
		count = __btree_for_each(head, geo, head->node, opaque, func,
				func2, 1, head->height, 0);
	__btree_init(head);
	return count;
}