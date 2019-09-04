#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct s2mpa01_info {unsigned int ramp_delay24; unsigned int ramp_delay3; unsigned int ramp_delay5; unsigned int ramp_delay16; unsigned int ramp_delay7; unsigned int ramp_delay8910; } ;
struct regulator_dev {TYPE_1__* desc; } ;
struct TYPE_2__ {unsigned int ramp_delay; unsigned int min_uV; unsigned int uV_step; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,unsigned int) ; 
#define  S2MPA01_BUCK1 137 
#define  S2MPA01_BUCK10 136 
#define  S2MPA01_BUCK2 135 
#define  S2MPA01_BUCK3 134 
#define  S2MPA01_BUCK4 133 
#define  S2MPA01_BUCK5 132 
#define  S2MPA01_BUCK6 131 
#define  S2MPA01_BUCK7 130 
#define  S2MPA01_BUCK8 129 
#define  S2MPA01_BUCK9 128 
 int /*<<< orphan*/  abs (int) ; 
 struct s2mpa01_info* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int s2mpa01_regulator_set_voltage_time_sel(struct regulator_dev *rdev,
				   unsigned int old_selector,
				   unsigned int new_selector)
{
	struct s2mpa01_info *s2mpa01 = rdev_get_drvdata(rdev);
	unsigned int ramp_delay = 0;
	int old_volt, new_volt;

	switch (rdev_get_id(rdev)) {
	case S2MPA01_BUCK2:
	case S2MPA01_BUCK4:
		ramp_delay = s2mpa01->ramp_delay24;
		break;
	case S2MPA01_BUCK3:
		ramp_delay = s2mpa01->ramp_delay3;
		break;
	case S2MPA01_BUCK5:
		ramp_delay = s2mpa01->ramp_delay5;
		break;
	case S2MPA01_BUCK1:
	case S2MPA01_BUCK6:
		ramp_delay = s2mpa01->ramp_delay16;
		break;
	case S2MPA01_BUCK7:
		ramp_delay = s2mpa01->ramp_delay7;
		break;
	case S2MPA01_BUCK8:
	case S2MPA01_BUCK9:
	case S2MPA01_BUCK10:
		ramp_delay = s2mpa01->ramp_delay8910;
		break;
	}

	if (ramp_delay == 0)
		ramp_delay = rdev->desc->ramp_delay;

	old_volt = rdev->desc->min_uV + (rdev->desc->uV_step * old_selector);
	new_volt = rdev->desc->min_uV + (rdev->desc->uV_step * new_selector);

	return DIV_ROUND_UP(abs(new_volt - old_volt), ramp_delay);
}