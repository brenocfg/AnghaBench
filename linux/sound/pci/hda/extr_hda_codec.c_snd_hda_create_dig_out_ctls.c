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
struct snd_kcontrol_new {scalar_t__ name; } ;
struct TYPE_3__ {int index; } ;
struct snd_kcontrol {scalar_t__ private_value; TYPE_1__ id; } ;
struct hda_spdif_out {int ctls; int /*<<< orphan*/  status; int /*<<< orphan*/  nid; } ;
struct TYPE_4__ {scalar_t__ used; } ;
struct hda_codec {int /*<<< orphan*/  core; TYPE_2__ spdif_out; struct hda_bus* bus; } ;
struct hda_bus {int primary_dig_out_type; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_GET_DIGI_CONVERT_1 ; 
 int EBUSY ; 
 int ENOMEM ; 
 int HDA_PCM_TYPE_HDMI ; 
 int HDA_PCM_TYPE_SPDIF ; 
 int /*<<< orphan*/  codec_err (struct hda_codec*,char*) ; 
 int /*<<< orphan*/  convert_to_spdif_status (int) ; 
 struct snd_kcontrol_new* dig_mixes ; 
 int find_empty_mixer_ctl_idx (struct hda_codec*,char*,int) ; 
 struct snd_kcontrol* find_mixer_ctl (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hda_spdif_out* snd_array_new (TYPE_2__*) ; 
 struct snd_kcontrol* snd_ctl_new1 (struct snd_kcontrol_new*,struct hda_codec*) ; 
 int snd_hda_ctl_add (struct hda_codec*,int /*<<< orphan*/ ,struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_hdac_regmap_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int snd_hda_create_dig_out_ctls(struct hda_codec *codec,
				hda_nid_t associated_nid,
				hda_nid_t cvt_nid,
				int type)
{
	int err;
	struct snd_kcontrol *kctl;
	struct snd_kcontrol_new *dig_mix;
	int idx = 0;
	int val = 0;
	const int spdif_index = 16;
	struct hda_spdif_out *spdif;
	struct hda_bus *bus = codec->bus;

	if (bus->primary_dig_out_type == HDA_PCM_TYPE_HDMI &&
	    type == HDA_PCM_TYPE_SPDIF) {
		idx = spdif_index;
	} else if (bus->primary_dig_out_type == HDA_PCM_TYPE_SPDIF &&
		   type == HDA_PCM_TYPE_HDMI) {
		/* suppose a single SPDIF device */
		for (dig_mix = dig_mixes; dig_mix->name; dig_mix++) {
			kctl = find_mixer_ctl(codec, dig_mix->name, 0, 0);
			if (!kctl)
				break;
			kctl->id.index = spdif_index;
		}
		bus->primary_dig_out_type = HDA_PCM_TYPE_HDMI;
	}
	if (!bus->primary_dig_out_type)
		bus->primary_dig_out_type = type;

	idx = find_empty_mixer_ctl_idx(codec, "IEC958 Playback Switch", idx);
	if (idx < 0) {
		codec_err(codec, "too many IEC958 outputs\n");
		return -EBUSY;
	}
	spdif = snd_array_new(&codec->spdif_out);
	if (!spdif)
		return -ENOMEM;
	for (dig_mix = dig_mixes; dig_mix->name; dig_mix++) {
		kctl = snd_ctl_new1(dig_mix, codec);
		if (!kctl)
			return -ENOMEM;
		kctl->id.index = idx;
		kctl->private_value = codec->spdif_out.used - 1;
		err = snd_hda_ctl_add(codec, associated_nid, kctl);
		if (err < 0)
			return err;
	}
	spdif->nid = cvt_nid;
	snd_hdac_regmap_read(&codec->core, cvt_nid,
			     AC_VERB_GET_DIGI_CONVERT_1, &val);
	spdif->ctls = val;
	spdif->status = convert_to_spdif_status(spdif->ctls);
	return 0;
}