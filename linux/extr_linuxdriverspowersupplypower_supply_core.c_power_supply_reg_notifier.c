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

/* Variables and functions */
 int atomic_notifier_chain_register (int /*<<< orphan*/ *,struct notifier_block*) ; 
 int /*<<< orphan*/  power_supply_notifier ; 

int power_supply_reg_notifier(struct notifier_block *nb)
{
	return atomic_notifier_chain_register(&power_supply_notifier, nb);
}