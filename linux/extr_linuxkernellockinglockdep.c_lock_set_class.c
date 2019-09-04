#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lockdep_map {int dummy; } ;
struct lock_class_key {int dummy; } ;
struct TYPE_3__ {int lockdep_recursion; } ;

/* Variables and functions */
 scalar_t__ __lock_set_class (struct lockdep_map*,char const*,struct lock_class_key*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  check_chain_key (TYPE_1__*) ; 
 int /*<<< orphan*/  check_flags (unsigned long) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  raw_local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  raw_local_irq_save (unsigned long) ; 
 scalar_t__ unlikely (int) ; 

void lock_set_class(struct lockdep_map *lock, const char *name,
		    struct lock_class_key *key, unsigned int subclass,
		    unsigned long ip)
{
	unsigned long flags;

	if (unlikely(current->lockdep_recursion))
		return;

	raw_local_irq_save(flags);
	current->lockdep_recursion = 1;
	check_flags(flags);
	if (__lock_set_class(lock, name, key, subclass, ip))
		check_chain_key(current);
	current->lockdep_recursion = 0;
	raw_local_irq_restore(flags);
}