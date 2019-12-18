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
struct notifier_block {int dummy; } ;
struct blocking_notifier_head {int /*<<< orphan*/  rwsem; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 scalar_t__ SYSTEM_BOOTING ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int notifier_chain_register (int /*<<< orphan*/ *,struct notifier_block*) ; 
 scalar_t__ system_state ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int blocking_notifier_chain_register(struct blocking_notifier_head *nh,
		struct notifier_block *n)
{
	int ret;

	/*
	 * This code gets used during boot-up, when task switching is
	 * not yet working and interrupts must remain disabled.  At
	 * such times we must not call down_write().
	 */
	if (unlikely(system_state == SYSTEM_BOOTING))
		return notifier_chain_register(&nh->head, n);

	down_write(&nh->rwsem);
	ret = notifier_chain_register(&nh->head, n);
	up_write(&nh->rwsem);
	return ret;
}