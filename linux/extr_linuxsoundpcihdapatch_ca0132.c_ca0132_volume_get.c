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
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {long* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {long* vnode_lvol; long* vnode_rvol; } ;
typedef  size_t hda_nid_t ;

/* Variables and functions */
 size_t VNODE_START_NID ; 
 int get_amp_channels (struct snd_kcontrol*) ; 
 size_t get_amp_nid (struct snd_kcontrol*) ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int ca0132_volume_get(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	struct ca0132_spec *spec = codec->spec;
	hda_nid_t nid = get_amp_nid(kcontrol);
	int ch = get_amp_channels(kcontrol);
	long *valp = ucontrol->value.integer.value;

	/* store the left and right volume */
	if (ch & 1) {
		*valp = spec->vnode_lvol[nid - VNODE_START_NID];
		valp++;
	}
	if (ch & 2) {
		*valp = spec->vnode_rvol[nid - VNODE_START_NID];
		valp++;
	}
	return 0;
}