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
typedef  int u8 ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA7213_ALC_CIC_OP_CHANNEL_LEFT ; 
 int /*<<< orphan*/  DA7213_ALC_CIC_OP_CHANNEL_RIGHT ; 
 int /*<<< orphan*/  DA7213_ALC_CTRL1 ; 
 int DA7213_ALC_OFFSET_15_8 ; 
 int DA7213_ALC_OFFSET_19_16 ; 
 int DA7213_ALC_OFFSET_EN ; 
 int /*<<< orphan*/  DA7213_ALC_OFFSET_MAN_M_L ; 
 int /*<<< orphan*/  DA7213_ALC_OFFSET_MAN_M_R ; 
 int /*<<< orphan*/  DA7213_ALC_OFFSET_MAN_U_L ; 
 int /*<<< orphan*/  DA7213_ALC_OFFSET_MAN_U_R ; 
 int DA7213_ALC_SYNC_MODE ; 
 int da7213_get_alc_data (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void da7213_alc_calib_man(struct snd_soc_component *component)
{
	u8 reg_val;
	int avg_left_data, avg_right_data, offset_l, offset_r;

	/* Calculate average for Left and Right data */
	/* Left Data */
	avg_left_data = da7213_get_alc_data(component,
			DA7213_ALC_CIC_OP_CHANNEL_LEFT);
	/* Right Data */
	avg_right_data = da7213_get_alc_data(component,
			 DA7213_ALC_CIC_OP_CHANNEL_RIGHT);

	/* Calculate DC offset */
	offset_l = -avg_left_data;
	offset_r = -avg_right_data;

	reg_val = (offset_l & DA7213_ALC_OFFSET_15_8) >> 8;
	snd_soc_component_write(component, DA7213_ALC_OFFSET_MAN_M_L, reg_val);
	reg_val = (offset_l & DA7213_ALC_OFFSET_19_16) >> 16;
	snd_soc_component_write(component, DA7213_ALC_OFFSET_MAN_U_L, reg_val);

	reg_val = (offset_r & DA7213_ALC_OFFSET_15_8) >> 8;
	snd_soc_component_write(component, DA7213_ALC_OFFSET_MAN_M_R, reg_val);
	reg_val = (offset_r & DA7213_ALC_OFFSET_19_16) >> 16;
	snd_soc_component_write(component, DA7213_ALC_OFFSET_MAN_U_R, reg_val);

	/* Enable analog/digital gain mode & offset cancellation */
	snd_soc_component_update_bits(component, DA7213_ALC_CTRL1,
			    DA7213_ALC_OFFSET_EN | DA7213_ALC_SYNC_MODE,
			    DA7213_ALC_OFFSET_EN | DA7213_ALC_SYNC_MODE);
}