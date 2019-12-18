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
struct wm_hubs_data {int dcs_readback_mode; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 
 int WM8993_DCS_DAC_WR_VAL_0_MASK ; 
 int WM8993_DCS_DAC_WR_VAL_1_MASK ; 
 int WM8993_DCS_DAC_WR_VAL_1_SHIFT ; 
 int WM8993_DCS_INTEG_CHAN_0_MASK ; 
 int WM8993_DCS_INTEG_CHAN_1_MASK ; 
 int WM8993_DC_SERVO_3 ; 
 int WM8993_DC_SERVO_READBACK_1 ; 
 int WM8993_DC_SERVO_READBACK_2 ; 
 int WM8994_DC_SERVO_4E ; 
 int WM8994_DC_SERVO_READBACK ; 
 struct wm_hubs_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int) ; 

__attribute__((used)) static int wm_hubs_read_dc_servo(struct snd_soc_component *component,
				  u16 *reg_l, u16 *reg_r)
{
	struct wm_hubs_data *hubs = snd_soc_component_get_drvdata(component);
	u16 dcs_reg, reg;
	int ret = 0;

	switch (hubs->dcs_readback_mode) {
	case 2:
		dcs_reg = WM8994_DC_SERVO_4E;
		break;
	case 1:
		dcs_reg = WM8994_DC_SERVO_READBACK;
		break;
	default:
		dcs_reg = WM8993_DC_SERVO_3;
		break;
	}

	/* Different chips in the family support different readback
	 * methods.
	 */
	switch (hubs->dcs_readback_mode) {
	case 0:
		*reg_l = snd_soc_component_read32(component, WM8993_DC_SERVO_READBACK_1)
			& WM8993_DCS_INTEG_CHAN_0_MASK;
		*reg_r = snd_soc_component_read32(component, WM8993_DC_SERVO_READBACK_2)
			& WM8993_DCS_INTEG_CHAN_1_MASK;
		break;
	case 2:
	case 1:
		reg = snd_soc_component_read32(component, dcs_reg);
		*reg_r = (reg & WM8993_DCS_DAC_WR_VAL_1_MASK)
			>> WM8993_DCS_DAC_WR_VAL_1_SHIFT;
		*reg_l = reg & WM8993_DCS_DAC_WR_VAL_0_MASK;
		break;
	default:
		WARN(1, "Unknown DCS readback method\n");
		ret = -1;
	}
	return ret;
}