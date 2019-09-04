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
struct rw_semaphore {scalar_t__ owner; int /*<<< orphan*/  dep_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_RWSEMS_WARN_ON (int) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  __downgrade_write (struct rw_semaphore*) ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  lock_downgrade (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwsem_set_reader_owned (struct rw_semaphore*) ; 

void downgrade_write(struct rw_semaphore *sem)
{
	lock_downgrade(&sem->dep_map, _RET_IP_);
	DEBUG_RWSEMS_WARN_ON(sem->owner != current);

	rwsem_set_reader_owned(sem);
	__downgrade_write(sem);
}