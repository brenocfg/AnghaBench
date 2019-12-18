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
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 scalar_t__ atomic_add_unless (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int _atomic_dec_and_lock_irqsave(atomic_t *atomic, spinlock_t *lock,
				 unsigned long *flags)
{
	/* Subtract 1 from counter unless that drops it to 0 (ie. it was 1) */
	if (atomic_add_unless(atomic, -1, 1))
		return 0;

	/* Otherwise do it the slow way */
	spin_lock_irqsave(lock, *flags);
	if (atomic_dec_and_test(atomic))
		return 1;
	spin_unlock_irqrestore(lock, *flags);
	return 0;
}