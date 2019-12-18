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
struct pending_free {int dummy; } ;
struct lockdep_map {int dummy; } ;
struct lock_class {int dummy; } ;

/* Variables and functions */
 int MAX_LOCKDEP_SUBCLASSES ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_locks_off () ; 
 int /*<<< orphan*/  lock_class_cache_is_registered (struct lockdep_map*) ; 
 struct lock_class* look_up_lock_class (struct lockdep_map*,int) ; 
 int /*<<< orphan*/  zap_class (struct pending_free*,struct lock_class*) ; 

__attribute__((used)) static void __lockdep_reset_lock(struct pending_free *pf,
				 struct lockdep_map *lock)
{
	struct lock_class *class;
	int j;

	/*
	 * Remove all classes this lock might have:
	 */
	for (j = 0; j < MAX_LOCKDEP_SUBCLASSES; j++) {
		/*
		 * If the class exists we look it up and zap it:
		 */
		class = look_up_lock_class(lock, j);
		if (class)
			zap_class(pf, class);
	}
	/*
	 * Debug check: in the end all mapped classes should
	 * be gone.
	 */
	if (WARN_ON_ONCE(lock_class_cache_is_registered(lock)))
		debug_locks_off();
}