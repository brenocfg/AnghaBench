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
struct snd_soc_dapm_widget {int shift; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAPM_POST_PMU 132 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
#define  WM8962_HPOUTL_PGA_ENA_SHIFT 131 
 int WM8962_HPOUTL_VOLUME ; 
#define  WM8962_HPOUTR_PGA_ENA_SHIFT 130 
 int WM8962_HPOUTR_VOLUME ; 
#define  WM8962_SPKOUTL_PGA_ENA_SHIFT 129 
 int WM8962_SPKOUTL_VOLUME ; 
#define  WM8962_SPKOUTR_PGA_ENA_SHIFT 128 
 int WM8962_SPKOUTR_VOLUME ; 
 int /*<<< orphan*/  snd_soc_component_read32 (struct snd_soc_component*,int) ; 
 int snd_soc_component_write (struct snd_soc_component*,int,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int out_pga_event(struct snd_soc_dapm_widget *w,
			 struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	int reg;

	switch (w->shift) {
	case WM8962_HPOUTR_PGA_ENA_SHIFT:
		reg = WM8962_HPOUTR_VOLUME;
		break;
	case WM8962_HPOUTL_PGA_ENA_SHIFT:
		reg = WM8962_HPOUTL_VOLUME;
		break;
	case WM8962_SPKOUTR_PGA_ENA_SHIFT:
		reg = WM8962_SPKOUTR_VOLUME;
		break;
	case WM8962_SPKOUTL_PGA_ENA_SHIFT:
		reg = WM8962_SPKOUTL_VOLUME;
		break;
	default:
		WARN(1, "Invalid shift %d\n", w->shift);
		return -EINVAL;
	}

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		return snd_soc_component_write(component, reg, snd_soc_component_read32(component, reg));
	default:
		WARN(1, "Invalid event %d\n", event);
		return -EINVAL;
	}
}