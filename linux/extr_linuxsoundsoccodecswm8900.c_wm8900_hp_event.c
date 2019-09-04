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
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
#define  SND_SOC_DAPM_POST_PMD 131 
#define  SND_SOC_DAPM_POST_PMU 130 
#define  SND_SOC_DAPM_PRE_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  WM8900_REG_HPCTL1 ; 
 int WM8900_REG_HPCTL1_HP_CLAMP_IP ; 
 int WM8900_REG_HPCTL1_HP_CLAMP_OP ; 
 int WM8900_REG_HPCTL1_HP_IPSTAGE_ENA ; 
 int WM8900_REG_HPCTL1_HP_OPSTAGE_ENA ; 
 int WM8900_REG_HPCTL1_HP_SHORT ; 
 int WM8900_REG_HPCTL1_HP_SHORT2 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8900_hp_event(struct snd_soc_dapm_widget *w,
			   struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u16 hpctl1 = snd_soc_component_read32(component, WM8900_REG_HPCTL1);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		/* Clamp headphone outputs */
		hpctl1 = WM8900_REG_HPCTL1_HP_CLAMP_IP |
			WM8900_REG_HPCTL1_HP_CLAMP_OP;
		snd_soc_component_write(component, WM8900_REG_HPCTL1, hpctl1);
		break;

	case SND_SOC_DAPM_POST_PMU:
		/* Enable the input stage */
		hpctl1 &= ~WM8900_REG_HPCTL1_HP_CLAMP_IP;
		hpctl1 |= WM8900_REG_HPCTL1_HP_SHORT |
			WM8900_REG_HPCTL1_HP_SHORT2 |
			WM8900_REG_HPCTL1_HP_IPSTAGE_ENA;
		snd_soc_component_write(component, WM8900_REG_HPCTL1, hpctl1);

		msleep(400);

		/* Enable the output stage */
		hpctl1 &= ~WM8900_REG_HPCTL1_HP_CLAMP_OP;
		hpctl1 |= WM8900_REG_HPCTL1_HP_OPSTAGE_ENA;
		snd_soc_component_write(component, WM8900_REG_HPCTL1, hpctl1);

		/* Remove the shorts */
		hpctl1 &= ~WM8900_REG_HPCTL1_HP_SHORT2;
		snd_soc_component_write(component, WM8900_REG_HPCTL1, hpctl1);
		hpctl1 &= ~WM8900_REG_HPCTL1_HP_SHORT;
		snd_soc_component_write(component, WM8900_REG_HPCTL1, hpctl1);
		break;

	case SND_SOC_DAPM_PRE_PMD:
		/* Short the output */
		hpctl1 |= WM8900_REG_HPCTL1_HP_SHORT;
		snd_soc_component_write(component, WM8900_REG_HPCTL1, hpctl1);

		/* Disable the output stage */
		hpctl1 &= ~WM8900_REG_HPCTL1_HP_OPSTAGE_ENA;
		snd_soc_component_write(component, WM8900_REG_HPCTL1, hpctl1);

		/* Clamp the outputs and power down input */
		hpctl1 |= WM8900_REG_HPCTL1_HP_CLAMP_IP |
			WM8900_REG_HPCTL1_HP_CLAMP_OP;
		hpctl1 &= ~WM8900_REG_HPCTL1_HP_IPSTAGE_ENA;
		snd_soc_component_write(component, WM8900_REG_HPCTL1, hpctl1);
		break;

	case SND_SOC_DAPM_POST_PMD:
		/* Disable everything */
		snd_soc_component_write(component, WM8900_REG_HPCTL1, 0);
		break;

	default:
		WARN(1, "Invalid event %d\n", event);
		break;
	}

	return 0;
}