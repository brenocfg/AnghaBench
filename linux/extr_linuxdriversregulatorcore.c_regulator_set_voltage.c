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
struct regulator {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM_SUSPEND_ON ; 
 int /*<<< orphan*/  regulator_lock_supply (int /*<<< orphan*/ ) ; 
 int regulator_set_voltage_unlocked (struct regulator*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_unlock_supply (int /*<<< orphan*/ ) ; 

int regulator_set_voltage(struct regulator *regulator, int min_uV, int max_uV)
{
	int ret = 0;

	regulator_lock_supply(regulator->rdev);

	ret = regulator_set_voltage_unlocked(regulator, min_uV, max_uV,
					     PM_SUSPEND_ON);

	regulator_unlock_supply(regulator->rdev);

	return ret;
}