#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {TYPE_2__* constraints; TYPE_1__* desc; } ;
struct TYPE_4__ {int ramp_delay; int settling_time; int settling_time_up; int settling_time_down; } ;
struct TYPE_3__ {int ramp_delay; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  abs (int) ; 
 int /*<<< orphan*/  rdev_dbg (struct regulator_dev*,char*) ; 

__attribute__((used)) static int _regulator_set_voltage_time(struct regulator_dev *rdev,
				       int old_uV, int new_uV)
{
	unsigned int ramp_delay = 0;

	if (rdev->constraints->ramp_delay)
		ramp_delay = rdev->constraints->ramp_delay;
	else if (rdev->desc->ramp_delay)
		ramp_delay = rdev->desc->ramp_delay;
	else if (rdev->constraints->settling_time)
		return rdev->constraints->settling_time;
	else if (rdev->constraints->settling_time_up &&
		 (new_uV > old_uV))
		return rdev->constraints->settling_time_up;
	else if (rdev->constraints->settling_time_down &&
		 (new_uV < old_uV))
		return rdev->constraints->settling_time_down;

	if (ramp_delay == 0) {
		rdev_dbg(rdev, "ramp_delay not set\n");
		return 0;
	}

	return DIV_ROUND_UP(abs(new_uV - old_uV), ramp_delay);
}