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
 int /*<<< orphan*/  WM9090_ANALOGUE_HP_0 ; 
 int /*<<< orphan*/  WM9090_CHARGE_PUMP_1 ; 
 int WM9090_CP_ENA ; 
 unsigned int WM9090_DCS_ENA_CHAN_0 ; 
 unsigned int WM9090_DCS_ENA_CHAN_1 ; 
 unsigned int WM9090_DCS_TRIG_STARTUP_0 ; 
 unsigned int WM9090_DCS_TRIG_STARTUP_1 ; 
 int /*<<< orphan*/  WM9090_DC_SERVO_0 ; 
 unsigned int WM9090_HPOUT1L_DLY ; 
 int WM9090_HPOUT1L_ENA ; 
 unsigned int WM9090_HPOUT1L_OUTP ; 
 unsigned int WM9090_HPOUT1L_RMV_SHORT ; 
 unsigned int WM9090_HPOUT1R_DLY ; 
 int WM9090_HPOUT1R_ENA ; 
 unsigned int WM9090_HPOUT1R_OUTP ; 
 unsigned int WM9090_HPOUT1R_RMV_SHORT ; 
 int /*<<< orphan*/  WM9090_POWER_MANAGEMENT_1 ; 
 int /*<<< orphan*/  msleep (int) ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_dc_servo (struct snd_soc_component*) ; 

__attribute__((used)) static int hp_ev(struct snd_soc_dapm_widget *w,
		 struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	unsigned int reg = snd_soc_component_read32(component, WM9090_ANALOGUE_HP_0);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, WM9090_CHARGE_PUMP_1,
				    WM9090_CP_ENA, WM9090_CP_ENA);

		msleep(5);

		snd_soc_component_update_bits(component, WM9090_POWER_MANAGEMENT_1,
				    WM9090_HPOUT1L_ENA | WM9090_HPOUT1R_ENA,
				    WM9090_HPOUT1L_ENA | WM9090_HPOUT1R_ENA);

		reg |= WM9090_HPOUT1L_DLY | WM9090_HPOUT1R_DLY;
		snd_soc_component_write(component, WM9090_ANALOGUE_HP_0, reg);

		/* Start the DC servo.  We don't currently use the
		 * ability to save the state since we don't have full
		 * control of the analogue paths and they can change
		 * DC offsets; see the WM8904 driver for an example of
		 * doing so.
		 */
		snd_soc_component_write(component, WM9090_DC_SERVO_0,
			      WM9090_DCS_ENA_CHAN_0 |
			      WM9090_DCS_ENA_CHAN_1 |
			      WM9090_DCS_TRIG_STARTUP_1 |
			      WM9090_DCS_TRIG_STARTUP_0);
		wait_for_dc_servo(component);

		reg |= WM9090_HPOUT1R_OUTP | WM9090_HPOUT1R_RMV_SHORT |
			WM9090_HPOUT1L_OUTP | WM9090_HPOUT1L_RMV_SHORT;
		snd_soc_component_write(component, WM9090_ANALOGUE_HP_0, reg);
		break;

	case SND_SOC_DAPM_PRE_PMD:
		reg &= ~(WM9090_HPOUT1L_RMV_SHORT |
			 WM9090_HPOUT1L_DLY |
			 WM9090_HPOUT1L_OUTP |
			 WM9090_HPOUT1R_RMV_SHORT |
			 WM9090_HPOUT1R_DLY |
			 WM9090_HPOUT1R_OUTP);

		snd_soc_component_write(component, WM9090_ANALOGUE_HP_0, reg);

		snd_soc_component_write(component, WM9090_DC_SERVO_0, 0);

		snd_soc_component_update_bits(component, WM9090_POWER_MANAGEMENT_1,
				    WM9090_HPOUT1L_ENA | WM9090_HPOUT1R_ENA,
				    0);

		snd_soc_component_update_bits(component, WM9090_CHARGE_PUMP_1,
				    WM9090_CP_ENA, 0);
		break;
	}

	return 0;
}