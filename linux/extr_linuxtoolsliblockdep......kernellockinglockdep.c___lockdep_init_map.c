#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lockdep_map {char* name; struct lock_class_key* key; int /*<<< orphan*/ ** class_cache; } ;
struct lock_class_key {int dummy; } ;
struct TYPE_2__ {int lockdep_recursion; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LOCKS_WARN_ON (int) ; 
 int NR_LOCKDEP_CACHING_CLASSES ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  debug_locks ; 
 int /*<<< orphan*/  printk (char*,struct lock_class_key*) ; 
 int /*<<< orphan*/  raw_local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  raw_local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  register_lock_class (struct lockdep_map*,int,int) ; 
 int /*<<< orphan*/  static_obj (struct lock_class_key*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void __lockdep_init_map(struct lockdep_map *lock, const char *name,
		      struct lock_class_key *key, int subclass)
{
	int i;

	for (i = 0; i < NR_LOCKDEP_CACHING_CLASSES; i++)
		lock->class_cache[i] = NULL;

#ifdef CONFIG_LOCK_STAT
	lock->cpu = raw_smp_processor_id();
#endif

	/*
	 * Can't be having no nameless bastards around this place!
	 */
	if (DEBUG_LOCKS_WARN_ON(!name)) {
		lock->name = "NULL";
		return;
	}

	lock->name = name;

	/*
	 * No key, no joy, we need to hash something.
	 */
	if (DEBUG_LOCKS_WARN_ON(!key))
		return;
	/*
	 * Sanity check, the lock-class key must be persistent:
	 */
	if (!static_obj(key)) {
		printk("BUG: key %px not in .data!\n", key);
		/*
		 * What it says above ^^^^^, I suggest you read it.
		 */
		DEBUG_LOCKS_WARN_ON(1);
		return;
	}
	lock->key = key;

	if (unlikely(!debug_locks))
		return;

	if (subclass) {
		unsigned long flags;

		if (DEBUG_LOCKS_WARN_ON(current->lockdep_recursion))
			return;

		raw_local_irq_save(flags);
		current->lockdep_recursion = 1;
		register_lock_class(lock, subclass, 1);
		current->lockdep_recursion = 0;
		raw_local_irq_restore(flags);
	}
}