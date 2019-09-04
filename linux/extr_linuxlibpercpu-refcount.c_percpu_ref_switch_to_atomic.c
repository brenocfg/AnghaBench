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
struct percpu_ref {int force_atomic; } ;
typedef  int /*<<< orphan*/  percpu_ref_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  __percpu_ref_switch_mode (struct percpu_ref*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_switch_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void percpu_ref_switch_to_atomic(struct percpu_ref *ref,
				 percpu_ref_func_t *confirm_switch)
{
	unsigned long flags;

	spin_lock_irqsave(&percpu_ref_switch_lock, flags);

	ref->force_atomic = true;
	__percpu_ref_switch_mode(ref, confirm_switch);

	spin_unlock_irqrestore(&percpu_ref_switch_lock, flags);
}