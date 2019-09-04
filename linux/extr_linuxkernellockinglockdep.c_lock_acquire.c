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
 int /*<<< orphan*/  __lock_acquire (struct lockdep_map*,unsigned int,int,int,int,int /*<<< orphan*/ ,struct lockdep_map*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_flags (unsigned long) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  irqs_disabled_flags (unsigned long) ; 
 int /*<<< orphan*/  raw_local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  raw_local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  trace_lock_acquire (struct lockdep_map*,unsigned int,int,int,int,struct lockdep_map*,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

void lock_acquire(struct lockdep_map *lock, unsigned int subclass,
			  int trylock, int read, int check,
			  struct lockdep_map *nest_lock, unsigned long ip)
{
	unsigned long flags;

	if (unlikely(current->lockdep_recursion))
		return;

	raw_local_irq_save(flags);
	check_flags(flags);

	current->lockdep_recursion = 1;
	trace_lock_acquire(lock, subclass, trylock, read, check, nest_lock, ip);
	__lock_acquire(lock, subclass, trylock, read, check,
		       irqs_disabled_flags(flags), nest_lock, ip, 0, 0);
	current->lockdep_recursion = 0;
	raw_local_irq_restore(flags);
}