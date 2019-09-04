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
typedef  int u16 ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 int wm831x_buckv_list_voltage (struct regulator_dev*,int) ; 

__attribute__((used)) static int wm831x_buckv_map_voltage(struct regulator_dev *rdev,
				   int min_uV, int max_uV)
{
	u16 vsel;

	if (min_uV < 600000)
		vsel = 0;
	else if (min_uV <= 1800000)
		vsel = DIV_ROUND_UP(min_uV - 600000, 12500) + 8;
	else
		return -EINVAL;

	if (wm831x_buckv_list_voltage(rdev, vsel) > max_uV)
		return -EINVAL;

	return vsel;
}