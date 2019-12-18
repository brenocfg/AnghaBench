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
struct snd_kcontrol_new {scalar_t__ name; } ;
struct snd_kcontrol {int /*<<< orphan*/  private_value; } ;
struct hda_codec {int spdif_in_enable; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int AC_DIG1_ENABLE ; 
 int /*<<< orphan*/  AC_VERB_GET_DIGI_CONVERT_1 ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  codec_err (struct hda_codec*,char*) ; 
 struct snd_kcontrol_new* dig_in_ctls ; 
 int find_empty_mixer_ctl_idx (struct hda_codec*,char*,int /*<<< orphan*/ ) ; 
 struct snd_kcontrol* snd_ctl_new1 (struct snd_kcontrol_new*,struct hda_codec*) ; 
 int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_hda_ctl_add (struct hda_codec*,int /*<<< orphan*/ ,struct snd_kcontrol*) ; 

int snd_hda_create_spdif_in_ctls(struct hda_codec *codec, hda_nid_t nid)
{
	int err;
	struct snd_kcontrol *kctl;
	struct snd_kcontrol_new *dig_mix;
	int idx;

	idx = find_empty_mixer_ctl_idx(codec, "IEC958 Capture Switch", 0);
	if (idx < 0) {
		codec_err(codec, "too many IEC958 inputs\n");
		return -EBUSY;
	}
	for (dig_mix = dig_in_ctls; dig_mix->name; dig_mix++) {
		kctl = snd_ctl_new1(dig_mix, codec);
		if (!kctl)
			return -ENOMEM;
		kctl->private_value = nid;
		err = snd_hda_ctl_add(codec, nid, kctl);
		if (err < 0)
			return err;
	}
	codec->spdif_in_enable =
		snd_hda_codec_read(codec, nid, 0,
				   AC_VERB_GET_DIGI_CONVERT_1, 0) &
		AC_DIG1_ENABLE;
	return 0;
}