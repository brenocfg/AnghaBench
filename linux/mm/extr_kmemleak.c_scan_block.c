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
struct kmemleak_object {unsigned long excess_ref; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 void* BYTES_PER_POINTER ; 
 unsigned long* PTR_ALIGN (void*,void*) ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 scalar_t__ color_gray (struct kmemleak_object*) ; 
 int /*<<< orphan*/  kasan_disable_current () ; 
 int /*<<< orphan*/  kasan_enable_current () ; 
 scalar_t__ kasan_reset_tag (void*) ; 
 int /*<<< orphan*/  kmemleak_lock ; 
 struct kmemleak_object* lookup_object (unsigned long,int) ; 
 unsigned long max_addr ; 
 unsigned long min_addr ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ scan_should_stop () ; 
 int /*<<< orphan*/  spin_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_refs (struct kmemleak_object*) ; 

__attribute__((used)) static void scan_block(void *_start, void *_end,
		       struct kmemleak_object *scanned)
{
	unsigned long *ptr;
	unsigned long *start = PTR_ALIGN(_start, BYTES_PER_POINTER);
	unsigned long *end = _end - (BYTES_PER_POINTER - 1);
	unsigned long flags;
	unsigned long untagged_ptr;

	read_lock_irqsave(&kmemleak_lock, flags);
	for (ptr = start; ptr < end; ptr++) {
		struct kmemleak_object *object;
		unsigned long pointer;
		unsigned long excess_ref;

		if (scan_should_stop())
			break;

		kasan_disable_current();
		pointer = *ptr;
		kasan_enable_current();

		untagged_ptr = (unsigned long)kasan_reset_tag((void *)pointer);
		if (untagged_ptr < min_addr || untagged_ptr >= max_addr)
			continue;

		/*
		 * No need for get_object() here since we hold kmemleak_lock.
		 * object->use_count cannot be dropped to 0 while the object
		 * is still present in object_tree_root and object_list
		 * (with updates protected by kmemleak_lock).
		 */
		object = lookup_object(pointer, 1);
		if (!object)
			continue;
		if (object == scanned)
			/* self referenced, ignore */
			continue;

		/*
		 * Avoid the lockdep recursive warning on object->lock being
		 * previously acquired in scan_object(). These locks are
		 * enclosed by scan_mutex.
		 */
		spin_lock_nested(&object->lock, SINGLE_DEPTH_NESTING);
		/* only pass surplus references (object already gray) */
		if (color_gray(object)) {
			excess_ref = object->excess_ref;
			/* no need for update_refs() if object already gray */
		} else {
			excess_ref = 0;
			update_refs(object);
		}
		spin_unlock(&object->lock);

		if (excess_ref) {
			object = lookup_object(excess_ref, 0);
			if (!object)
				continue;
			if (object == scanned)
				/* circular reference, ignore */
				continue;
			spin_lock_nested(&object->lock, SINGLE_DEPTH_NESTING);
			update_refs(object);
			spin_unlock(&object->lock);
		}
	}
	read_unlock_irqrestore(&kmemleak_lock, flags);
}