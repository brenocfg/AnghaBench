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
struct kmemleak_object {int /*<<< orphan*/  object_list; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct kmemleak_object*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct kmemleak_object*) ; 
 int /*<<< orphan*/  kmemleak_lock ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct kmemleak_object* mem_pool ; 
 int /*<<< orphan*/  mem_pool_free_list ; 
 int /*<<< orphan*/  object_cache ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mem_pool_free(struct kmemleak_object *object)
{
	unsigned long flags;

	if (object < mem_pool || object >= mem_pool + ARRAY_SIZE(mem_pool)) {
		kmem_cache_free(object_cache, object);
		return;
	}

	/* add the object to the memory pool free list */
	write_lock_irqsave(&kmemleak_lock, flags);
	list_add(&object->object_list, &mem_pool_free_list);
	write_unlock_irqrestore(&kmemleak_lock, flags);
}