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
 unsigned long RWSEM_RD_NONSPINNABLE ; 
 unsigned long RWSEM_READER_OWNED ; 
 unsigned long atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_set (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void __rwsem_set_reader_owned(struct rw_semaphore *sem,
					    struct task_struct *owner)
{
	unsigned long val = (unsigned long)owner | RWSEM_READER_OWNED |
		(atomic_long_read(&sem->owner) & RWSEM_RD_NONSPINNABLE);

	atomic_long_set(&sem->owner, val);
}