#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct soc_mixer_control {unsigned int shift; unsigned int max; } ;
struct snd_soc_pcm_runtime {TYPE_2__** codec_dais; } ;
struct snd_soc_card {TYPE_1__* dai_link; struct glb_pool* drvdata; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_7__ {unsigned int* value; } ;
struct TYPE_8__ {TYPE_3__ integer; } ;
struct snd_ctl_elem_value {TYPE_4__ value; } ;
struct glb_pool {int dual_mode; } ;
struct TYPE_6__ {int /*<<< orphan*/  component; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCM512x_DIGITAL_VOLUME_2 ; 
 int /*<<< orphan*/  PCM512x_DIGITAL_VOLUME_3 ; 
 struct snd_soc_card* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int snd_soc_component_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct snd_soc_pcm_runtime* snd_soc_get_pcm_runtime (struct snd_soc_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcm512x_get_reg_sub(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;
	struct snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	struct glb_pool *glb_ptr = card->drvdata;
	struct snd_soc_pcm_runtime *rtd;
	unsigned int left_val = 0;
	unsigned int right_val = 0;
	int ret;
	rtd = snd_soc_get_pcm_runtime(card, card->dai_link[0].name);
	ret = snd_soc_component_read(rtd->codec_dais[1]->component,
			PCM512x_DIGITAL_VOLUME_3, &right_val);
	if (ret < 0)
		return ret;

	if (glb_ptr->dual_mode != 1) {
		ret = snd_soc_component_read(rtd->codec_dais[1]->component,
				PCM512x_DIGITAL_VOLUME_2, &left_val);
		if ( ret < 0)
			return ret;

	} else {
		left_val = right_val;
	}

	ucontrol->value.integer.value[0] =
				(~(left_val >> mc->shift)) & mc->max;
	ucontrol->value.integer.value[1] =
				(~(right_val >> mc->shift)) & mc->max;

	return 0;
}