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
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct adau1977 {int type; } ;

/* Variables and functions */
#define  ADAU1977 128 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adau1977_micbias_dapm_widgets ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct adau1977* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adau1977_component_probe(struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct adau1977 *adau1977 = snd_soc_component_get_drvdata(component);
	int ret;

	switch (adau1977->type) {
	case ADAU1977:
		ret = snd_soc_dapm_new_controls(dapm,
			adau1977_micbias_dapm_widgets,
			ARRAY_SIZE(adau1977_micbias_dapm_widgets));
		if (ret < 0)
			return ret;
		break;
	default:
		break;
	}

	return 0;
}