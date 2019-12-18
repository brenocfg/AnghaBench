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
 int /*<<< orphan*/  RWSEM_READER_OWNED ; 
 long RWSEM_WRITER_MASK ; 
 long atomic_long_read (int /*<<< orphan*/ *) ; 
 int rwsem_test_oflags (struct rw_semaphore*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool is_rwsem_reader_owned(struct rw_semaphore *sem)
{
#ifdef CONFIG_DEBUG_RWSEMS
	/*
	 * Check the count to see if it is write-locked.
	 */
	long count = atomic_long_read(&sem->count);

	if (count & RWSEM_WRITER_MASK)
		return false;
#endif
	return rwsem_test_oflags(sem, RWSEM_READER_OWNED);
}