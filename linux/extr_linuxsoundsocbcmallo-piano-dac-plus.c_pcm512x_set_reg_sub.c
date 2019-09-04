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
struct soc_mixer_control {unsigned int max; } ;
struct snd_soc_pcm_runtime {TYPE_4__** codec_dais; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; TYPE_3__* dai_link; struct glb_pool* drvdata; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_5__ {unsigned int* value; } ;
struct TYPE_6__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct glb_pool {int dual_mode; } ;
struct TYPE_8__ {int /*<<< orphan*/  component; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCM512x_DIGITAL_VOLUME_2 ; 
 int /*<<< orphan*/  PCM512x_DIGITAL_VOLUME_3 ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ digital_gain_0db_limit ; 
 struct snd_soc_card* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int snd_soc_component_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct snd_soc_pcm_runtime* snd_soc_get_pcm_runtime (struct snd_soc_card*,int /*<<< orphan*/ ) ; 
 int snd_soc_limit_volume (struct snd_soc_card*,char*,int) ; 

__attribute__((used)) static int pcm512x_set_reg_sub(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;
	struct snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	struct glb_pool *glb_ptr = card->drvdata;
	struct snd_soc_pcm_runtime *rtd;
	unsigned int left_val = (ucontrol->value.integer.value[0] & mc->max);
	unsigned int right_val = (ucontrol->value.integer.value[1] & mc->max);
	int ret = 0;

	rtd = snd_soc_get_pcm_runtime(card, card->dai_link[0].name);
	if (glb_ptr->dual_mode != 1) {
		ret = snd_soc_component_write(rtd->codec_dais[1]->component,
				PCM512x_DIGITAL_VOLUME_2, (~left_val));
		if (ret < 0)
			return ret;
	}

	if (digital_gain_0db_limit) {
		ret = snd_soc_limit_volume(card, "Subwoofer Playback Volume",
					207);
		if (ret < 0)
			dev_warn(card->dev, "Failed to set volume limit: %d\n",
				ret);
	}

	ret = snd_soc_component_write(rtd->codec_dais[1]->component,
			PCM512x_DIGITAL_VOLUME_3, (~right_val));
	if (ret < 0)
		return ret;

	return 1;
}