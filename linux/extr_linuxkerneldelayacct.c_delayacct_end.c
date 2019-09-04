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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  raw_spinlock_t ;

/* Variables and functions */
 scalar_t__ ktime_get_ns () ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void delayacct_end(raw_spinlock_t *lock, u64 *start, u64 *total,
			  u32 *count)
{
	s64 ns = ktime_get_ns() - *start;
	unsigned long flags;

	if (ns > 0) {
		raw_spin_lock_irqsave(lock, flags);
		*total += ns;
		(*count)++;
		raw_spin_unlock_irqrestore(lock, flags);
	}
}