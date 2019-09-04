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
 int /*<<< orphan*/  down_read_trylock (struct rw_semaphore*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (struct rw_semaphore*) ; 

__attribute__((used)) static inline bool rwsem_is_wrlocked(struct rw_semaphore *sem)
{
	bool wrlocked = true;

	if (unlikely(down_read_trylock(sem))) {
		wrlocked = false;
		up_read(sem);
	}

	return wrlocked;
}