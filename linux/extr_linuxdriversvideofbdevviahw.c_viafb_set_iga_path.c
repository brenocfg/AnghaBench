#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_8__* shared; TYPE_7__* chip_info; TYPE_5__* lvds_setting_info2; TYPE_3__* lvds_setting_info; TYPE_1__* tmds_setting_info; } ;
struct TYPE_17__ {int iga1_devices; int iga2_devices; } ;
struct TYPE_15__ {int /*<<< orphan*/  output_interface; } ;
struct TYPE_13__ {int /*<<< orphan*/  output_interface; } ;
struct TYPE_11__ {int /*<<< orphan*/  output_interface; } ;
struct TYPE_16__ {scalar_t__ gfx_chip_name; TYPE_6__ lvds_chip_info2; TYPE_4__ lvds_chip_info; TYPE_2__ tmds_chip_info; } ;
struct TYPE_14__ {int iga_path; } ;
struct TYPE_12__ {int iga_path; } ;
struct TYPE_10__ {int iga_path; } ;

/* Variables and functions */
 scalar_t__ CRT_Device ; 
 scalar_t__ DVI_Device ; 
 int IGA1 ; 
 void* IGA2 ; 
 scalar_t__ LCD2_Device ; 
 scalar_t__ LCD_Device ; 
 scalar_t__ UNICHROME_CLE266 ; 
 int VIA_CRT ; 
 int VIA_DVP1 ; 
 int VIA_LVDS2 ; 
 int get_dvi_devices (int /*<<< orphan*/ ) ; 
 int get_lcd_devices (int /*<<< orphan*/ ) ; 
 scalar_t__ machine_is_olpc () ; 
 scalar_t__ viafb_CRT_ON ; 
 scalar_t__ viafb_DVI_ON ; 
 scalar_t__ viafb_LCD2_ON ; 
 scalar_t__ viafb_LCD_ON ; 
 int viafb_SAMM_ON ; 
 scalar_t__ viafb_dual_fb ; 
 scalar_t__ viafb_primary_dev ; 
 TYPE_9__* viaparinfo ; 

void viafb_set_iga_path(void)
{
	int crt_iga_path = 0;

	if (viafb_SAMM_ON == 1) {
		if (viafb_CRT_ON) {
			if (viafb_primary_dev == CRT_Device)
				crt_iga_path = IGA1;
			else
				crt_iga_path = IGA2;
		}

		if (viafb_DVI_ON) {
			if (viafb_primary_dev == DVI_Device)
				viaparinfo->tmds_setting_info->iga_path = IGA1;
			else
				viaparinfo->tmds_setting_info->iga_path = IGA2;
		}

		if (viafb_LCD_ON) {
			if (viafb_primary_dev == LCD_Device) {
				if (viafb_dual_fb &&
					(viaparinfo->chip_info->gfx_chip_name ==
					UNICHROME_CLE266)) {
					viaparinfo->
					lvds_setting_info->iga_path = IGA2;
					crt_iga_path = IGA1;
					viaparinfo->
					tmds_setting_info->iga_path = IGA1;
				} else
					viaparinfo->
					lvds_setting_info->iga_path = IGA1;
			} else {
				viaparinfo->lvds_setting_info->iga_path = IGA2;
			}
		}
		if (viafb_LCD2_ON) {
			if (LCD2_Device == viafb_primary_dev)
				viaparinfo->lvds_setting_info2->iga_path = IGA1;
			else
				viaparinfo->lvds_setting_info2->iga_path = IGA2;
		}
	} else {
		viafb_SAMM_ON = 0;

		if (viafb_CRT_ON && viafb_LCD_ON) {
			crt_iga_path = IGA1;
			viaparinfo->lvds_setting_info->iga_path = IGA2;
		} else if (viafb_CRT_ON && viafb_DVI_ON) {
			crt_iga_path = IGA1;
			viaparinfo->tmds_setting_info->iga_path = IGA2;
		} else if (viafb_LCD_ON && viafb_DVI_ON) {
			viaparinfo->tmds_setting_info->iga_path = IGA1;
			viaparinfo->lvds_setting_info->iga_path = IGA2;
		} else if (viafb_LCD_ON && viafb_LCD2_ON) {
			viaparinfo->lvds_setting_info->iga_path = IGA2;
			viaparinfo->lvds_setting_info2->iga_path = IGA2;
		} else if (viafb_CRT_ON) {
			crt_iga_path = IGA1;
		} else if (viafb_LCD_ON) {
			viaparinfo->lvds_setting_info->iga_path = IGA2;
		} else if (viafb_DVI_ON) {
			viaparinfo->tmds_setting_info->iga_path = IGA1;
		}
	}

	viaparinfo->shared->iga1_devices = 0;
	viaparinfo->shared->iga2_devices = 0;
	if (viafb_CRT_ON) {
		if (crt_iga_path == IGA1)
			viaparinfo->shared->iga1_devices |= VIA_CRT;
		else
			viaparinfo->shared->iga2_devices |= VIA_CRT;
	}

	if (viafb_DVI_ON) {
		if (viaparinfo->tmds_setting_info->iga_path == IGA1)
			viaparinfo->shared->iga1_devices |= get_dvi_devices(
				viaparinfo->chip_info->
				tmds_chip_info.output_interface);
		else
			viaparinfo->shared->iga2_devices |= get_dvi_devices(
				viaparinfo->chip_info->
				tmds_chip_info.output_interface);
	}

	if (viafb_LCD_ON) {
		if (viaparinfo->lvds_setting_info->iga_path == IGA1)
			viaparinfo->shared->iga1_devices |= get_lcd_devices(
				viaparinfo->chip_info->
				lvds_chip_info.output_interface);
		else
			viaparinfo->shared->iga2_devices |= get_lcd_devices(
				viaparinfo->chip_info->
				lvds_chip_info.output_interface);
	}

	if (viafb_LCD2_ON) {
		if (viaparinfo->lvds_setting_info2->iga_path == IGA1)
			viaparinfo->shared->iga1_devices |= get_lcd_devices(
				viaparinfo->chip_info->
				lvds_chip_info2.output_interface);
		else
			viaparinfo->shared->iga2_devices |= get_lcd_devices(
				viaparinfo->chip_info->
				lvds_chip_info2.output_interface);
	}

	/* looks like the OLPC has its display wired to DVP1 and LVDS2 */
	if (machine_is_olpc())
		viaparinfo->shared->iga2_devices = VIA_DVP1 | VIA_LVDS2;
}