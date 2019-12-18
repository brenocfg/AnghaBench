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
struct kmemleak_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_object (struct kmemleak_object*) ; 
 int /*<<< orphan*/  kmemleak_lock ; 
 struct kmemleak_object* lookup_object (unsigned long,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct kmemleak_object *find_and_get_object(unsigned long ptr, int alias)
{
	unsigned long flags;
	struct kmemleak_object *object;

	rcu_read_lock();
	read_lock_irqsave(&kmemleak_lock, flags);
	object = lookup_object(ptr, alias);
	read_unlock_irqrestore(&kmemleak_lock, flags);

	/* check whether the object is still available */
	if (object && !get_object(object))
		object = NULL;
	rcu_read_unlock();

	return object;
}