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
struct rw_semaphore {int /*<<< orphan*/  dep_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  _RET_IP_ ; 
 int __down_read_trylock (struct rw_semaphore*) ; 
 int /*<<< orphan*/  rwsem_acquire_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwsem_set_reader_owned (struct rw_semaphore*) ; 

int down_read_trylock(struct rw_semaphore *sem)
{
	int ret = __down_read_trylock(sem);

	if (ret == 1) {
		rwsem_acquire_read(&sem->dep_map, 0, 1, _RET_IP_);
		rwsem_set_reader_owned(sem);
	}
	return ret;
}