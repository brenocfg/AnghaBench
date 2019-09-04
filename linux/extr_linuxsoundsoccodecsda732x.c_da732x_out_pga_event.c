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
struct snd_soc_dapm_widget {int shift; int /*<<< orphan*/  reg; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int DA732X_OUT_HIZ_DIS ; 
 int DA732X_OUT_HIZ_EN ; 
 int EINVAL ; 
#define  SND_SOC_DAPM_POST_PMD 129 
#define  SND_SOC_DAPM_POST_PMU 128 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da732x_out_pga_event(struct snd_soc_dapm_widget *w,
				struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component, w->reg,
				    (1 << w->shift) | DA732X_OUT_HIZ_EN,
				    (1 << w->shift) | DA732X_OUT_HIZ_EN);
		break;
	case SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component, w->reg,
				    (1 << w->shift) | DA732X_OUT_HIZ_EN,
				    (1 << w->shift) | DA732X_OUT_HIZ_DIS);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}