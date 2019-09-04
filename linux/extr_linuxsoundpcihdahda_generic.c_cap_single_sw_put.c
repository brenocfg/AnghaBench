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
struct hda_gen_spec {int /*<<< orphan*/  (* cap_sync_hook ) (struct hda_codec*,struct snd_kcontrol*,struct snd_ctl_elem_value*) ;} ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 int snd_hda_mixer_amp_switch_put (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  stub1 (struct hda_codec*,struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 

__attribute__((used)) static int cap_single_sw_put(struct snd_kcontrol *kcontrol,
			     struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	struct hda_gen_spec *spec = codec->spec;
	int ret;

	ret = snd_hda_mixer_amp_switch_put(kcontrol, ucontrol);
	if (ret < 0)
		return ret;

	if (spec->cap_sync_hook)
		spec->cap_sync_hook(codec, kcontrol, ucontrol);

	return ret;
}