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
struct kmemleak_scan_area {unsigned long start; size_t size; int /*<<< orphan*/  node; } ;
struct kmemleak_object {unsigned long pointer; unsigned long size; int /*<<< orphan*/  lock; int /*<<< orphan*/  area_list; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJECT_FULL_SCAN ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  dump_object_info (struct kmemleak_object*) ; 
 struct kmemleak_object* find_and_get_object (unsigned long,int) ; 
 int /*<<< orphan*/  gfp_kmemleak_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct kmemleak_scan_area* kmem_cache_alloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (scalar_t__,struct kmemleak_scan_area*) ; 
 int /*<<< orphan*/  kmemleak_warn (char*,unsigned long) ; 
 int /*<<< orphan*/  pr_warn_once (char*) ; 
 int /*<<< orphan*/  put_object (struct kmemleak_object*) ; 
 scalar_t__ scan_area_cache ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void add_scan_area(unsigned long ptr, size_t size, gfp_t gfp)
{
	unsigned long flags;
	struct kmemleak_object *object;
	struct kmemleak_scan_area *area = NULL;

	object = find_and_get_object(ptr, 1);
	if (!object) {
		kmemleak_warn("Adding scan area to unknown object at 0x%08lx\n",
			      ptr);
		return;
	}

	if (scan_area_cache)
		area = kmem_cache_alloc(scan_area_cache, gfp_kmemleak_mask(gfp));

	spin_lock_irqsave(&object->lock, flags);
	if (!area) {
		pr_warn_once("Cannot allocate a scan area, scanning the full object\n");
		/* mark the object for full scan to avoid false positives */
		object->flags |= OBJECT_FULL_SCAN;
		goto out_unlock;
	}
	if (size == SIZE_MAX) {
		size = object->pointer + object->size - ptr;
	} else if (ptr + size > object->pointer + object->size) {
		kmemleak_warn("Scan area larger than object 0x%08lx\n", ptr);
		dump_object_info(object);
		kmem_cache_free(scan_area_cache, area);
		goto out_unlock;
	}

	INIT_HLIST_NODE(&area->node);
	area->start = ptr;
	area->size = size;

	hlist_add_head(&area->node, &object->area_list);
out_unlock:
	spin_unlock_irqrestore(&object->lock, flags);
	put_object(object);
}