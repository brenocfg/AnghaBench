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
struct TYPE_2__ {int /*<<< orphan*/  lcd_mode; int /*<<< orphan*/  panel_id; int /*<<< orphan*/  display_center; } ;
struct viafb_ioctl_setting {TYPE_1__ lcd_attributes; int /*<<< orphan*/  second_dev_ver_res; int /*<<< orphan*/  second_dev_hor_res; int /*<<< orphan*/  first_dev_ver_res; int /*<<< orphan*/  first_dev_hor_res; int /*<<< orphan*/  second_dev_refresh; int /*<<< orphan*/  first_dev_refresh; int /*<<< orphan*/  second_dev_bpp; int /*<<< orphan*/  first_dev_bpp; int /*<<< orphan*/  primary_device; int /*<<< orphan*/  samm_status; int /*<<< orphan*/  device_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_Device ; 
 int /*<<< orphan*/  DVI_Device ; 
 int /*<<< orphan*/  LCD2_Device ; 
 int /*<<< orphan*/  LCD_Device ; 
 int /*<<< orphan*/  get_primary_device () ; 
 int viafb_CRT_ON ; 
 int viafb_DVI_ON ; 
 int viafb_LCD2_ON ; 
 int viafb_LCD_ON ; 
 int /*<<< orphan*/  viafb_SAMM_ON ; 
 int /*<<< orphan*/  viafb_bpp ; 
 int /*<<< orphan*/  viafb_bpp1 ; 
 int /*<<< orphan*/  viafb_hotplug_Xres ; 
 int /*<<< orphan*/  viafb_hotplug_Yres ; 
 int /*<<< orphan*/  viafb_lcd_dsp_method ; 
 int /*<<< orphan*/  viafb_lcd_mode ; 
 int /*<<< orphan*/  viafb_lcd_panel_id ; 
 int /*<<< orphan*/  viafb_refresh ; 
 int /*<<< orphan*/  viafb_refresh1 ; 
 int /*<<< orphan*/  viafb_second_xres ; 
 int /*<<< orphan*/  viafb_second_yres ; 

__attribute__((used)) static void retrieve_device_setting(struct viafb_ioctl_setting
	*setting_info)
{

	/* get device status */
	if (viafb_CRT_ON == 1)
		setting_info->device_status = CRT_Device;
	if (viafb_DVI_ON == 1)
		setting_info->device_status |= DVI_Device;
	if (viafb_LCD_ON == 1)
		setting_info->device_status |= LCD_Device;
	if (viafb_LCD2_ON == 1)
		setting_info->device_status |= LCD2_Device;

	setting_info->samm_status = viafb_SAMM_ON;
	setting_info->primary_device = get_primary_device();

	setting_info->first_dev_bpp = viafb_bpp;
	setting_info->second_dev_bpp = viafb_bpp1;

	setting_info->first_dev_refresh = viafb_refresh;
	setting_info->second_dev_refresh = viafb_refresh1;

	setting_info->first_dev_hor_res = viafb_hotplug_Xres;
	setting_info->first_dev_ver_res = viafb_hotplug_Yres;
	setting_info->second_dev_hor_res = viafb_second_xres;
	setting_info->second_dev_ver_res = viafb_second_yres;

	/* Get lcd attributes */
	setting_info->lcd_attributes.display_center = viafb_lcd_dsp_method;
	setting_info->lcd_attributes.panel_id = viafb_lcd_panel_id;
	setting_info->lcd_attributes.lcd_mode = viafb_lcd_mode;
}