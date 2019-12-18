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
struct task_struct {int dummy; } ;
struct rw_semaphore {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 unsigned long RWSEM_OWNER_FLAGS_MASK ; 
 unsigned long atomic_long_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct task_struct *
rwsem_owner_flags(struct rw_semaphore *sem, unsigned long *pflags)
{
	unsigned long owner = atomic_long_read(&sem->owner);

	*pflags = owner & RWSEM_OWNER_FLAGS_MASK;
	return (struct task_struct *)(owner & ~RWSEM_OWNER_FLAGS_MASK);
}