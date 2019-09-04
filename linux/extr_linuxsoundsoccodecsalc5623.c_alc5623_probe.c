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
struct alc5623_priv {int id; scalar_t__ jack_det_ctrl; scalar_t__ add_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALC5623_ADD_CTRL_REG ; 
 int /*<<< orphan*/  ALC5623_JACK_DET_CTRL ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  alc5621_vol_snd_controls ; 
 int /*<<< orphan*/  alc5622_vol_snd_controls ; 
 int /*<<< orphan*/  alc5623_dapm_amp_widgets ; 
 int /*<<< orphan*/  alc5623_dapm_widgets ; 
 int /*<<< orphan*/  alc5623_reset (struct snd_soc_component*) ; 
 int /*<<< orphan*/  alc5623_snd_controls ; 
 int /*<<< orphan*/  alc5623_vol_snd_controls ; 
 int /*<<< orphan*/  intercon ; 
 int /*<<< orphan*/  intercon_amp_spk ; 
 int /*<<< orphan*/  intercon_spk ; 
 int /*<<< orphan*/  snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct alc5623_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (struct snd_soc_dapm_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alc5623_probe(struct snd_soc_component *component)
{
	struct alc5623_priv *alc5623 = snd_soc_component_get_drvdata(component);
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	alc5623_reset(component);

	if (alc5623->add_ctrl) {
		snd_soc_component_write(component, ALC5623_ADD_CTRL_REG,
				alc5623->add_ctrl);
	}

	if (alc5623->jack_det_ctrl) {
		snd_soc_component_write(component, ALC5623_JACK_DET_CTRL,
				alc5623->jack_det_ctrl);
	}

	switch (alc5623->id) {
	case 0x21:
		snd_soc_add_component_controls(component, alc5621_vol_snd_controls,
			ARRAY_SIZE(alc5621_vol_snd_controls));
		break;
	case 0x22:
		snd_soc_add_component_controls(component, alc5622_vol_snd_controls,
			ARRAY_SIZE(alc5622_vol_snd_controls));
		break;
	case 0x23:
		snd_soc_add_component_controls(component, alc5623_vol_snd_controls,
			ARRAY_SIZE(alc5623_vol_snd_controls));
		break;
	default:
		return -EINVAL;
	}

	snd_soc_add_component_controls(component, alc5623_snd_controls,
			ARRAY_SIZE(alc5623_snd_controls));

	snd_soc_dapm_new_controls(dapm, alc5623_dapm_widgets,
					ARRAY_SIZE(alc5623_dapm_widgets));

	/* set up audio path interconnects */
	snd_soc_dapm_add_routes(dapm, intercon, ARRAY_SIZE(intercon));

	switch (alc5623->id) {
	case 0x21:
	case 0x22:
		snd_soc_dapm_new_controls(dapm, alc5623_dapm_amp_widgets,
					ARRAY_SIZE(alc5623_dapm_amp_widgets));
		snd_soc_dapm_add_routes(dapm, intercon_amp_spk,
					ARRAY_SIZE(intercon_amp_spk));
		break;
	case 0x23:
		snd_soc_dapm_add_routes(dapm, intercon_spk,
					ARRAY_SIZE(intercon_spk));
		break;
	default:
		return -EINVAL;
	}

	return 0;
}