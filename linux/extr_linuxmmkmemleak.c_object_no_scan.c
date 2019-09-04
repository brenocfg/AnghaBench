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
struct kmemleak_object {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJECT_NO_SCAN ; 
 struct kmemleak_object* find_and_get_object (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemleak_warn (char*,unsigned long) ; 
 int /*<<< orphan*/  put_object (struct kmemleak_object*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void object_no_scan(unsigned long ptr)
{
	unsigned long flags;
	struct kmemleak_object *object;

	object = find_and_get_object(ptr, 0);
	if (!object) {
		kmemleak_warn("Not scanning unknown object at 0x%08lx\n", ptr);
		return;
	}

	spin_lock_irqsave(&object->lock, flags);
	object->flags |= OBJECT_NO_SCAN;
	spin_unlock_irqrestore(&object->lock, flags);
	put_object(object);
}