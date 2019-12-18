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
struct snd_kcontrol {int dummy; } ;
struct snd_ctl_elem_value {int dummy; } ;
struct hda_codec {struct conexant_spec* spec; } ;
struct conexant_spec {scalar_t__ dc_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  olpc_xo_update_mic_boost (struct hda_codec*) ; 
 int snd_hda_mixer_amp_volume_put (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int olpc_xo_mic_boost_put(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	struct conexant_spec *spec = codec->spec;
	int ret = snd_hda_mixer_amp_volume_put(kcontrol, ucontrol);
	if (ret > 0 && spec->dc_enable)
		olpc_xo_update_mic_boost(codec);
	return ret;
}