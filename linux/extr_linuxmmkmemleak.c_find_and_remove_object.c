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
struct kmemleak_object {int /*<<< orphan*/  object_list; int /*<<< orphan*/  rb_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmemleak_lock ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 struct kmemleak_object* lookup_object (unsigned long,int) ; 
 int /*<<< orphan*/  object_tree_root ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct kmemleak_object *find_and_remove_object(unsigned long ptr, int alias)
{
	unsigned long flags;
	struct kmemleak_object *object;

	write_lock_irqsave(&kmemleak_lock, flags);
	object = lookup_object(ptr, alias);
	if (object) {
		rb_erase(&object->rb_node, &object_tree_root);
		list_del_rcu(&object->object_list);
	}
	write_unlock_irqrestore(&kmemleak_lock, flags);

	return object;
}