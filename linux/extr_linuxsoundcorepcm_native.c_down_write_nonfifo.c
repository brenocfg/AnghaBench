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
 int /*<<< orphan*/  down_write_trylock (struct rw_semaphore*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static inline void down_write_nonfifo(struct rw_semaphore *lock)
{
	while (!down_write_trylock(lock))
		msleep(1);
}