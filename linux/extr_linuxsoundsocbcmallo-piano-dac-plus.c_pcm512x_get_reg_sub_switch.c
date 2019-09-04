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
struct snd_soc_pcm_runtime {TYPE_2__** codec_dais; } ;
struct snd_soc_card {TYPE_1__* dai_link; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_7__ {void** value; } ;
struct TYPE_8__ {TYPE_3__ integer; } ;
struct snd_ctl_elem_value {TYPE_4__ value; } ;
struct TYPE_6__ {int /*<<< orphan*/  component; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCM512x_MUTE ; 
 int P_DAC_LEFT_MUTE ; 
 int P_DAC_RIGHT_MUTE ; 
 void* P_MUTE ; 
 void* P_UNMUTE ; 
 struct snd_soc_card* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int snd_soc_component_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct snd_soc_pcm_runtime* snd_soc_get_pcm_runtime (struct snd_soc_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcm512x_get_reg_sub_switch(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	struct snd_soc_pcm_runtime *rtd;
	int val = 0;
	int ret;

	rtd = snd_soc_get_pcm_runtime(card, card->dai_link[0].name);
	ret = snd_soc_component_read(rtd->codec_dais[1]->component, PCM512x_MUTE, &val);
	if (ret < 0)
		return ret;

	ucontrol->value.integer.value[0] =
			(val & P_DAC_LEFT_MUTE) ? P_UNMUTE : P_MUTE;
	ucontrol->value.integer.value[1] =
			(val & P_DAC_RIGHT_MUTE) ? P_UNMUTE : P_MUTE;

	return val;
}