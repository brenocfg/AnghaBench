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
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMD 128 
 int /*<<< orphan*/  WM8995_ANALOGUE_HP_1 ; 
 int /*<<< orphan*/  WM8995_CHARGE_PUMP_1 ; 
 int WM8995_CP_ENA ; 
 int WM8995_CP_ENA_MASK ; 
 unsigned int WM8995_DCS_ENA_CHAN_0 ; 
 unsigned int WM8995_DCS_ENA_CHAN_1 ; 
 int WM8995_DCS_TRIG_DAC_WR_0 ; 
 int WM8995_DCS_TRIG_DAC_WR_1 ; 
 int WM8995_DCS_TRIG_STARTUP_0 ; 
 int WM8995_DCS_TRIG_STARTUP_1 ; 
 int /*<<< orphan*/  WM8995_DC_SERVO_1 ; 
 int /*<<< orphan*/  WM8995_DC_SERVO_2 ; 
 unsigned int WM8995_HPOUT1L_DLY ; 
 int WM8995_HPOUT1L_DLY_MASK ; 
 int WM8995_HPOUT1L_ENA ; 
 int WM8995_HPOUT1L_ENA_MASK ; 
 unsigned int WM8995_HPOUT1L_OUTP ; 
 int WM8995_HPOUT1L_OUTP_MASK ; 
 unsigned int WM8995_HPOUT1L_RMV_SHORT ; 
 int WM8995_HPOUT1L_RMV_SHORT_MASK ; 
 unsigned int WM8995_HPOUT1R_DLY ; 
 int WM8995_HPOUT1R_DLY_MASK ; 
 int WM8995_HPOUT1R_ENA ; 
 int WM8995_HPOUT1R_ENA_MASK ; 
 unsigned int WM8995_HPOUT1R_OUTP ; 
 int WM8995_HPOUT1R_OUTP_MASK ; 
 unsigned int WM8995_HPOUT1R_RMV_SHORT ; 
 int WM8995_HPOUT1R_RMV_SHORT_MASK ; 
 int /*<<< orphan*/  WM8995_POWER_MANAGEMENT_1 ; 
 int /*<<< orphan*/  dc_servo_cmd (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int hp_event(struct snd_soc_dapm_widget *w,
		    struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	unsigned int reg;

	reg = snd_soc_component_read32(component, WM8995_ANALOGUE_HP_1);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, WM8995_CHARGE_PUMP_1,
				    WM8995_CP_ENA_MASK, WM8995_CP_ENA);

		msleep(5);

		snd_soc_component_update_bits(component, WM8995_POWER_MANAGEMENT_1,
				    WM8995_HPOUT1L_ENA_MASK |
				    WM8995_HPOUT1R_ENA_MASK,
				    WM8995_HPOUT1L_ENA | WM8995_HPOUT1R_ENA);

		udelay(20);

		reg |= WM8995_HPOUT1L_DLY | WM8995_HPOUT1R_DLY;
		snd_soc_component_write(component, WM8995_ANALOGUE_HP_1, reg);

		snd_soc_component_write(component, WM8995_DC_SERVO_1, WM8995_DCS_ENA_CHAN_0 |
			      WM8995_DCS_ENA_CHAN_1);

		dc_servo_cmd(component, WM8995_DC_SERVO_2,
			     WM8995_DCS_TRIG_STARTUP_0 |
			     WM8995_DCS_TRIG_STARTUP_1,
			     WM8995_DCS_TRIG_DAC_WR_0 |
			     WM8995_DCS_TRIG_DAC_WR_1);

		reg |= WM8995_HPOUT1R_OUTP | WM8995_HPOUT1R_RMV_SHORT |
		       WM8995_HPOUT1L_OUTP | WM8995_HPOUT1L_RMV_SHORT;
		snd_soc_component_write(component, WM8995_ANALOGUE_HP_1, reg);

		break;
	case SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component, WM8995_ANALOGUE_HP_1,
				    WM8995_HPOUT1L_OUTP_MASK |
				    WM8995_HPOUT1R_OUTP_MASK |
				    WM8995_HPOUT1L_RMV_SHORT_MASK |
				    WM8995_HPOUT1R_RMV_SHORT_MASK, 0);

		snd_soc_component_update_bits(component, WM8995_ANALOGUE_HP_1,
				    WM8995_HPOUT1L_DLY_MASK |
				    WM8995_HPOUT1R_DLY_MASK, 0);

		snd_soc_component_write(component, WM8995_DC_SERVO_1, 0);

		snd_soc_component_update_bits(component, WM8995_POWER_MANAGEMENT_1,
				    WM8995_HPOUT1L_ENA_MASK |
				    WM8995_HPOUT1R_ENA_MASK,
				    0);
		break;
	}

	return 0;
}