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
struct lvds_chip_information {int /*<<< orphan*/  lvds_chip_slave_addr; int /*<<< orphan*/  i2c_port; } ;
struct IODATA {int Index; int Mask; int Data; } ;

/* Variables and functions */
 int viafb_gpio_i2c_read_lvds (struct lvds_setting_information*,struct lvds_chip_information*,int) ; 
 int /*<<< orphan*/  viafb_i2c_writebyte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void viafb_gpio_i2c_write_mask_lvds(struct lvds_setting_information
			      *plvds_setting_info, struct lvds_chip_information
			      *plvds_chip_info, struct IODATA io_data)
{
	int index, data;

	index = io_data.Index;
	data = viafb_gpio_i2c_read_lvds(plvds_setting_info, plvds_chip_info,
		index);
	data = (data & (~io_data.Mask)) | io_data.Data;

	viafb_i2c_writebyte(plvds_chip_info->i2c_port,
			    plvds_chip_info->lvds_chip_slave_addr, index, data);
}