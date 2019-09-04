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
struct snd_soc_pcm_runtime {TYPE_4__** codec_dais; } ;
struct snd_soc_card {TYPE_3__* dai_link; struct glb_pool* drvdata; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_5__ {unsigned int* value; } ;
struct TYPE_6__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct glb_pool {int set_mode; } ;
struct TYPE_8__ {int /*<<< orphan*/  component; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCM512x_MUTE ; 
 struct snd_soc_card* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int snd_soc_component_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct snd_soc_pcm_runtime* snd_soc_get_pcm_runtime (struct snd_soc_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcm512x_set_reg_sub_switch(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	struct snd_soc_pcm_runtime *rtd;
	struct glb_pool *glb_ptr = card->drvdata;
	unsigned int left_val = (ucontrol->value.integer.value[0]);
	unsigned int right_val = (ucontrol->value.integer.value[1]);
	int ret = 0;

	rtd = snd_soc_get_pcm_runtime(card, card->dai_link[0].name);
	if (glb_ptr->set_mode != 1) {
		ret = snd_soc_component_write(rtd->codec_dais[1]->component, PCM512x_MUTE,
				~((left_val & 0x01)<<4 | (right_val & 0x01)));
		if (ret < 0)
			return ret;
	}
	return 1;

}