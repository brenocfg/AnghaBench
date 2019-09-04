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
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 scalar_t__ atomic_cmp_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sched_yield () ; 

__attribute__((used)) static inline int fpm_spinlock(atomic_t *lock, int try_once) /* {{{ */
{
	if (try_once) {
		return atomic_cmp_set(lock, 0, 1) ? 1 : 0;
	}

	for (;;) {

		if (atomic_cmp_set(lock, 0, 1)) {
			break;
		}

		sched_yield();
	}

	return 1;
}