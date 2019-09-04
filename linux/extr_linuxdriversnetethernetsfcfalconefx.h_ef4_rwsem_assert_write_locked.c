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
struct rw_semaphore {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read_trylock (struct rw_semaphore*) ; 
 int /*<<< orphan*/  up_read (struct rw_semaphore*) ; 

__attribute__((used)) static inline bool ef4_rwsem_assert_write_locked(struct rw_semaphore *sem)
{
	if (WARN_ON(down_read_trylock(sem))) {
		up_read(sem);
		return false;
	}
	return true;
}