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
struct percpu_ref {int /*<<< orphan*/  percpu_count_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __PERCPU_REF_DEAD ; 
 int /*<<< orphan*/  __percpu_ref_switch_mode (struct percpu_ref*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_get (struct percpu_ref*) ; 
 int /*<<< orphan*/  percpu_ref_is_zero (struct percpu_ref*) ; 
 int /*<<< orphan*/  percpu_ref_switch_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void percpu_ref_reinit(struct percpu_ref *ref)
{
	unsigned long flags;

	spin_lock_irqsave(&percpu_ref_switch_lock, flags);

	WARN_ON_ONCE(!percpu_ref_is_zero(ref));

	ref->percpu_count_ptr &= ~__PERCPU_REF_DEAD;
	percpu_ref_get(ref);
	__percpu_ref_switch_mode(ref, NULL);

	spin_unlock_irqrestore(&percpu_ref_switch_lock, flags);
}