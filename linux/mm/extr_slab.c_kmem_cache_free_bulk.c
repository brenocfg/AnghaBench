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
struct kmem_cache {int flags; int /*<<< orphan*/  object_size; } ;

/* Variables and functions */
 int SLAB_DEBUG_OBJECTS ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  __cache_free (struct kmem_cache*,void*,int /*<<< orphan*/ ) ; 
 struct kmem_cache* cache_from_obj (struct kmem_cache*,void*) ; 
 int /*<<< orphan*/  debug_check_no_locks_freed (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_check_no_obj_freed (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 struct kmem_cache* virt_to_cache (void*) ; 

void kmem_cache_free_bulk(struct kmem_cache *orig_s, size_t size, void **p)
{
	struct kmem_cache *s;
	size_t i;

	local_irq_disable();
	for (i = 0; i < size; i++) {
		void *objp = p[i];

		if (!orig_s) /* called via kfree_bulk */
			s = virt_to_cache(objp);
		else
			s = cache_from_obj(orig_s, objp);
		if (!s)
			continue;

		debug_check_no_locks_freed(objp, s->object_size);
		if (!(s->flags & SLAB_DEBUG_OBJECTS))
			debug_check_no_obj_freed(objp, s->object_size);

		__cache_free(s, objp, _RET_IP_);
	}
	local_irq_enable();

	/* FIXME: add tracing */
}