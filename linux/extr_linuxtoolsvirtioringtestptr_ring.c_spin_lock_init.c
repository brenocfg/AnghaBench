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
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int pthread_spin_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spin_lock_init(spinlock_t *lock)
{
	int r = pthread_spin_init(lock, 0);
	assert(!r);
}