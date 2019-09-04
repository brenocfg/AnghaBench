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
struct assoc_array_ptr {int dummy; } ;
struct assoc_array {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 struct assoc_array_ptr* READ_ONCE (int /*<<< orphan*/ ) ; 
 int assoc_array_subtree_iterate (struct assoc_array_ptr*,int /*<<< orphan*/ *,int (*) (void const*,void*),void*) ; 

int assoc_array_iterate(const struct assoc_array *array,
			int (*iterator)(const void *object,
					void *iterator_data),
			void *iterator_data)
{
	struct assoc_array_ptr *root = READ_ONCE(array->root); /* Address dependency. */

	if (!root)
		return 0;
	return assoc_array_subtree_iterate(root, NULL, iterator, iterator_data);
}