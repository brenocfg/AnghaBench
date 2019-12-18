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
struct snd_ctl_elem_info {int dummy; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int snd_hda_enum_helper_info (struct snd_kcontrol*,struct snd_ctl_elem_info*,int,char const* const*) ; 
 int snd_hda_get_num_conns (struct hda_codec*,int) ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int ad1988_auto_smux_enum_info(struct snd_kcontrol *kcontrol,
				      struct snd_ctl_elem_info *uinfo)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	static const char * const texts[] = {
		"PCM", "ADC1", "ADC2", "ADC3",
	};
	int num_conns = snd_hda_get_num_conns(codec, 0x0b) + 1;
	if (num_conns > 4)
		num_conns = 4;
	return snd_hda_enum_helper_info(kcontrol, uinfo, num_conns, texts);
}