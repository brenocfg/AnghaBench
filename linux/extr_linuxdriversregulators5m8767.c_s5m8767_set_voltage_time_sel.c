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
struct sec_voltage_desc {unsigned int step; } ;
struct s5m8767_info {int ramp_delay; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (unsigned int,int) ; 
 struct s5m8767_info* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 struct sec_voltage_desc** reg_voltage_map ; 

__attribute__((used)) static int s5m8767_set_voltage_time_sel(struct regulator_dev *rdev,
					     unsigned int old_sel,
					     unsigned int new_sel)
{
	struct s5m8767_info *s5m8767 = rdev_get_drvdata(rdev);
	const struct sec_voltage_desc *desc;
	int reg_id = rdev_get_id(rdev);

	desc = reg_voltage_map[reg_id];

	if ((old_sel < new_sel) && s5m8767->ramp_delay)
		return DIV_ROUND_UP(desc->step * (new_sel - old_sel),
					s5m8767->ramp_delay * 1000);
	return 0;
}