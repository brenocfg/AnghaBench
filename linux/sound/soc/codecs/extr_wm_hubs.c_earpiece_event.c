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
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  WM8993_ANTIPOP1 ; 
 int WM8993_HPOUT2_IN_ENA ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int earpiece_event(struct snd_soc_dapm_widget *w,
			  struct snd_kcontrol *control, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u16 reg = snd_soc_component_read32(component, WM8993_ANTIPOP1) & ~WM8993_HPOUT2_IN_ENA;

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		reg |= WM8993_HPOUT2_IN_ENA;
		snd_soc_component_write(component, WM8993_ANTIPOP1, reg);
		udelay(50);
		break;

	case SND_SOC_DAPM_POST_PMD:
		snd_soc_component_write(component, WM8993_ANTIPOP1, reg);
		break;

	default:
		WARN(1, "Invalid event %d\n", event);
		break;
	}

	return 0;
}