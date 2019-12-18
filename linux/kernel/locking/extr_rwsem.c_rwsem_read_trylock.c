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
struct rw_semaphore {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  RWSEM_READER_BIAS ; 
 long RWSEM_READ_FAILED_MASK ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 long atomic_long_add_return_acquire (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwsem_set_nonspinnable (struct rw_semaphore*) ; 

__attribute__((used)) static inline bool rwsem_read_trylock(struct rw_semaphore *sem)
{
	long cnt = atomic_long_add_return_acquire(RWSEM_READER_BIAS, &sem->count);
	if (WARN_ON_ONCE(cnt < 0))
		rwsem_set_nonspinnable(sem);
	return !(cnt & RWSEM_READ_FAILED_MASK);
}