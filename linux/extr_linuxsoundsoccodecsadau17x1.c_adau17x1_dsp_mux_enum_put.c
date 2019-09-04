#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct soc_enum {unsigned int shift_l; scalar_t__ items; } ;
struct snd_soc_dapm_update {int mask; int reg; unsigned int val; struct snd_kcontrol* kcontrol; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {scalar_t__* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct adau {int* dsp_bypass; int* tdm_slot; } ;

/* Variables and functions */
 int ADAU17X1_SERIAL_INPUT_ROUTE ; 
 int ADAU17X1_SERIAL_OUTPUT_ROUTE ; 
 int EINVAL ; 
 unsigned int SNDRV_PCM_STREAM_PLAYBACK ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct adau* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 unsigned int snd_soc_component_test_bits (struct snd_soc_component*,int,int,unsigned int) ; 
 struct snd_soc_component* snd_soc_dapm_kcontrol_component (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mux_update_power (struct snd_soc_dapm_context*,struct snd_kcontrol*,scalar_t__,struct soc_enum*,struct snd_soc_dapm_update*) ; 

__attribute__((used)) static int adau17x1_dsp_mux_enum_put(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	struct adau *adau = snd_soc_component_get_drvdata(component);
	struct soc_enum *e = (struct soc_enum *)kcontrol->private_value;
	struct snd_soc_dapm_update update = {};
	unsigned int stream = e->shift_l;
	unsigned int val, change;
	int reg;

	if (ucontrol->value.enumerated.item[0] >= e->items)
		return -EINVAL;

	switch (ucontrol->value.enumerated.item[0]) {
	case 0:
		val = 0;
		adau->dsp_bypass[stream] = false;
		break;
	default:
		val = (adau->tdm_slot[stream] * 2) + 1;
		adau->dsp_bypass[stream] = true;
		break;
	}

	if (stream == SNDRV_PCM_STREAM_PLAYBACK)
		reg = ADAU17X1_SERIAL_INPUT_ROUTE;
	else
		reg = ADAU17X1_SERIAL_OUTPUT_ROUTE;

	change = snd_soc_component_test_bits(component, reg, 0xff, val);
	if (change) {
		update.kcontrol = kcontrol;
		update.mask = 0xff;
		update.reg = reg;
		update.val = val;

		snd_soc_dapm_mux_update_power(dapm, kcontrol,
				ucontrol->value.enumerated.item[0], e, &update);
	}

	return change;
}