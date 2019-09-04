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
struct kmemleak_object {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  use_count; } ;

/* Variables and functions */
 int OBJECT_ALLOCATED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_object (struct kmemleak_object*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void __delete_object(struct kmemleak_object *object)
{
	unsigned long flags;

	WARN_ON(!(object->flags & OBJECT_ALLOCATED));
	WARN_ON(atomic_read(&object->use_count) < 1);

	/*
	 * Locking here also ensures that the corresponding memory block
	 * cannot be freed when it is being scanned.
	 */
	spin_lock_irqsave(&object->lock, flags);
	object->flags &= ~OBJECT_ALLOCATED;
	spin_unlock_irqrestore(&object->lock, flags);
	put_object(object);
}