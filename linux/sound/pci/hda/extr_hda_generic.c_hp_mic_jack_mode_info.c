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
struct snd_kcontrol {int /*<<< orphan*/  private_value; } ;
struct TYPE_3__ {int items; int item; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_info {int count; TYPE_2__ value; int /*<<< orphan*/  type; } ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_ENUMERATED ; 
 int get_in_jack_num_items (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int get_out_jack_num_items (struct hda_codec*,int /*<<< orphan*/ ) ; 
 unsigned int get_vref_caps (struct hda_codec*,int /*<<< orphan*/ ) ; 
 size_t get_vref_idx (unsigned int,int) ; 
 char** out_jack_texts ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 char** vref_texts ; 

__attribute__((used)) static int hp_mic_jack_mode_info(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_info *uinfo)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	hda_nid_t nid = kcontrol->private_value;
	int out_jacks = get_out_jack_num_items(codec, nid);
	int in_jacks = get_in_jack_num_items(codec, nid);
	const char *text = NULL;
	int idx;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.enumerated.items = out_jacks + in_jacks;
	if (uinfo->value.enumerated.item >= uinfo->value.enumerated.items)
		uinfo->value.enumerated.item = uinfo->value.enumerated.items - 1;
	idx = uinfo->value.enumerated.item;
	if (idx < out_jacks) {
		if (out_jacks > 1)
			text = out_jack_texts[idx];
		else
			text = "Headphone Out";
	} else {
		idx -= out_jacks;
		if (in_jacks > 1) {
			unsigned int vref_caps = get_vref_caps(codec, nid);
			text = vref_texts[get_vref_idx(vref_caps, idx)];
		} else
			text = "Mic In";
	}

	strcpy(uinfo->value.enumerated.name, text);
	return 0;
}