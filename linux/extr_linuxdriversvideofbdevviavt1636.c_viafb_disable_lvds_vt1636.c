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
struct lvds_setting_information {int dummy; } ;
struct lvds_chip_information {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vdd_off_data ; 
 int /*<<< orphan*/  viafb_gpio_i2c_write_mask_lvds (struct lvds_setting_information*,struct lvds_chip_information*,int /*<<< orphan*/ ) ; 

void viafb_disable_lvds_vt1636(struct lvds_setting_information
			 *plvds_setting_info,
			 struct lvds_chip_information *plvds_chip_info)
{
	viafb_gpio_i2c_write_mask_lvds(plvds_setting_info, plvds_chip_info,
		vdd_off_data);
}