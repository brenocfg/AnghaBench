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
 scalar_t__ RWSEM_READER_OWNED ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  __up_read (struct rw_semaphore*) ; 
 int /*<<< orphan*/  rwsem_release (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void up_read(struct rw_semaphore *sem)
{
	rwsem_release(&sem->dep_map, 1, _RET_IP_);
	DEBUG_RWSEMS_WARN_ON(sem->owner != RWSEM_READER_OWNED);

	__up_read(sem);
}