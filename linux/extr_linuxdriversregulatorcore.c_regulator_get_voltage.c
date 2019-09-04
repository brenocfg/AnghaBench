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
 int _regulator_get_voltage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_lock_supply (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_unlock_supply (int /*<<< orphan*/ ) ; 

int regulator_get_voltage(struct regulator *regulator)
{
	int ret;

	regulator_lock_supply(regulator->rdev);

	ret = _regulator_get_voltage(regulator->rdev);

	regulator_unlock_supply(regulator->rdev);

	return ret;
}