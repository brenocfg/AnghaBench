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
struct kmemleak_object {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dump_object_info (struct kmemleak_object*) ; 
 struct kmemleak_object* find_and_get_object (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long) ; 
 int /*<<< orphan*/  put_object (struct kmemleak_object*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dump_str_object_info(const char *str)
{
	unsigned long flags;
	struct kmemleak_object *object;
	unsigned long addr;

	if (kstrtoul(str, 0, &addr))
		return -EINVAL;
	object = find_and_get_object(addr, 0);
	if (!object) {
		pr_info("Unknown object at 0x%08lx\n", addr);
		return -EINVAL;
	}

	spin_lock_irqsave(&object->lock, flags);
	dump_object_info(object);
	spin_unlock_irqrestore(&object->lock, flags);

	put_object(object);
	return 0;
}