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
struct ca0132_spec {long* fx_ctl_val; } ;
typedef  int hda_nid_t ;

/* Variables and functions */
 int EFFECT_START_NID ; 
 int /*<<< orphan*/  ca0132_alt_slider_ctl_set (struct hda_codec*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  float_zero_to_one_lookup ; 
 int get_amp_nid (struct snd_kcontrol*) ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int ca0132_alt_effect_slider_put(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	struct ca0132_spec *spec = codec->spec;
	hda_nid_t nid = get_amp_nid(kcontrol);
	long *valp = ucontrol->value.integer.value;
	int idx;

	idx = nid - EFFECT_START_NID;
	/* any change? */
	if (spec->fx_ctl_val[idx] == *valp)
		return 0;

	spec->fx_ctl_val[idx] = *valp;

	idx = *valp;
	ca0132_alt_slider_ctl_set(codec, nid, float_zero_to_one_lookup, idx);

	return 0;
}