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
typedef  int /*<<< orphan*/  refcount_t ;

/* Variables and functions */
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_not_one (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool refcount_dec_and_lock_irqsave(refcount_t *r, spinlock_t *lock,
				   unsigned long *flags)
{
	if (refcount_dec_not_one(r))
		return false;

	spin_lock_irqsave(lock, *flags);
	if (!refcount_dec_and_test(r)) {
		spin_unlock_irqrestore(lock, *flags);
		return false;
	}

	return true;
}