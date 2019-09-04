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
struct snd_soc_dapm_widget {int /*<<< orphan*/  shift; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5682_PWR_ANLG_1 ; 
 int /*<<< orphan*/  RT5682_PWR_FV1 ; 
 int /*<<< orphan*/  RT5682_PWR_FV2 ; 
#define  RT5682_PWR_VREF1_BIT 131 
#define  RT5682_PWR_VREF2_BIT 130 
#define  SND_SOC_DAPM_POST_PMU 129 
#define  SND_SOC_DAPM_PRE_PMU 128 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int rt5655_set_verf(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);

	switch (event) {
	case SND_SOC_DAPM_PRE_PMU:
		switch (w->shift) {
		case RT5682_PWR_VREF1_BIT:
			snd_soc_component_update_bits(component,
				RT5682_PWR_ANLG_1, RT5682_PWR_FV1, 0);
			break;

		case RT5682_PWR_VREF2_BIT:
			snd_soc_component_update_bits(component,
				RT5682_PWR_ANLG_1, RT5682_PWR_FV2, 0);
			break;

		default:
			break;
		}
		break;

	case SND_SOC_DAPM_POST_PMU:
		usleep_range(15000, 20000);
		switch (w->shift) {
		case RT5682_PWR_VREF1_BIT:
			snd_soc_component_update_bits(component,
				RT5682_PWR_ANLG_1, RT5682_PWR_FV1,
				RT5682_PWR_FV1);
			break;

		case RT5682_PWR_VREF2_BIT:
			snd_soc_component_update_bits(component,
				RT5682_PWR_ANLG_1, RT5682_PWR_FV2,
				RT5682_PWR_FV2);
			break;

		default:
			break;
		}
		break;

	default:
		return 0;
	}

	return 0;
}