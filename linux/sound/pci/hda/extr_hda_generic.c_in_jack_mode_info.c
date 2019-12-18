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
struct TYPE_3__ {int /*<<< orphan*/  item; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_info {TYPE_2__ value; } ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int get_vref_caps (struct hda_codec*,int /*<<< orphan*/ ) ; 
 size_t get_vref_idx (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hweight32 (unsigned int) ; 
 int /*<<< orphan*/  snd_hda_enum_helper_info (struct snd_kcontrol*,struct snd_ctl_elem_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vref_texts ; 

__attribute__((used)) static int in_jack_mode_info(struct snd_kcontrol *kcontrol,
			     struct snd_ctl_elem_info *uinfo)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	hda_nid_t nid = kcontrol->private_value;
	unsigned int vref_caps = get_vref_caps(codec, nid);

	snd_hda_enum_helper_info(kcontrol, uinfo, hweight32(vref_caps),
				 vref_texts);
	/* set the right text */
	strcpy(uinfo->value.enumerated.name,
	       vref_texts[get_vref_idx(vref_caps, uinfo->value.enumerated.item)]);
	return 0;
}