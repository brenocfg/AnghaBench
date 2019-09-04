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
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int WM831X_BUCKV_MAX_SELECTOR ; 

__attribute__((used)) static int wm831x_buckv_list_voltage(struct regulator_dev *rdev,
				      unsigned selector)
{
	if (selector <= 0x8)
		return 600000;
	if (selector <= WM831X_BUCKV_MAX_SELECTOR)
		return 600000 + ((selector - 0x8) * 12500);
	return -EINVAL;
}