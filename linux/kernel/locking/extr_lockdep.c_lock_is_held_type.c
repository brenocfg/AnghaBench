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
struct lockdep_map {int dummy; } ;
struct TYPE_2__ {int lockdep_recursion; } ;

/* Variables and functions */
 int __lock_is_held (struct lockdep_map const*,int) ; 
 int /*<<< orphan*/  check_flags (unsigned long) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  raw_local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  raw_local_irq_save (unsigned long) ; 
 scalar_t__ unlikely (int) ; 

int lock_is_held_type(const struct lockdep_map *lock, int read)
{
	unsigned long flags;
	int ret = 0;

	if (unlikely(current->lockdep_recursion))
		return 1; /* avoid false negative lockdep_assert_held() */

	raw_local_irq_save(flags);
	check_flags(flags);

	current->lockdep_recursion = 1;
	ret = __lock_is_held(lock, read);
	current->lockdep_recursion = 0;
	raw_local_irq_restore(flags);

	return ret;
}