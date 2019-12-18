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
typedef  int slock_t ;

/* Variables and functions */
 int NUM_SPINLOCK_SEMAPHORES ; 

void
s_init_lock_sema(volatile slock_t *lock, bool nested)
{
	static int	counter = 0;

	*lock = ((++counter) % NUM_SPINLOCK_SEMAPHORES) + 1;
}