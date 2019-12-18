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
struct ca0132_spec {long* vnode_lswitch; long* vnode_rswitch; long* effects_switch; scalar_t__* input_pins; long cur_mic_boost; scalar_t__ in_enum_val; scalar_t__ cur_mic_type; long zxr_gain_set; scalar_t__ cur_out_type; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 scalar_t__ CRYSTAL_VOICE ; 
 scalar_t__ DIGITAL_MIC ; 
 scalar_t__ EFFECT_START_NID ; 
 scalar_t__ HEADPHONE_OUT ; 
 scalar_t__ IN_EFFECT_END_NID ; 
 scalar_t__ IN_EFFECT_START_NID ; 
 scalar_t__ OUT_EFFECT_END_NID ; 
 scalar_t__ OUT_EFFECT_START_NID ; 
 scalar_t__ PLAY_ENHANCEMENT ; 
 scalar_t__ REAR_LINE_IN ; 
 scalar_t__ VNODE_END_NID ; 
 scalar_t__ VNODE_START_NID ; 
 scalar_t__ ZXR_HEADPHONE_GAIN ; 
 int ca0132_cvoice_switch_set (struct hda_codec*) ; 
 int ca0132_effects_set (struct hda_codec*,scalar_t__,long) ; 
 int ca0132_mic_boost_set (struct hda_codec*,long) ; 
 int ca0132_pe_switch_set (struct hda_codec*) ; 
 scalar_t__ ca0132_use_alt_functions (struct ca0132_spec*) ; 
 int ca0132_vnode_switch_set (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,scalar_t__,long) ; 
 int get_amp_channels (struct snd_kcontrol*) ; 
 scalar_t__ get_amp_nid (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_hda_power_down (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_power_up (struct hda_codec*) ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int zxr_headphone_gain_set (struct hda_codec*,long) ; 

__attribute__((used)) static int ca0132_switch_put(struct snd_kcontrol *kcontrol,
			     struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	struct ca0132_spec *spec = codec->spec;
	hda_nid_t nid = get_amp_nid(kcontrol);
	int ch = get_amp_channels(kcontrol);
	long *valp = ucontrol->value.integer.value;
	int changed = 1;

	codec_dbg(codec, "ca0132_switch_put: nid=0x%x, val=%ld\n",
		    nid, *valp);

	snd_hda_power_up(codec);
	/* vnode */
	if ((nid >= VNODE_START_NID) && (nid < VNODE_END_NID)) {
		if (ch & 1) {
			spec->vnode_lswitch[nid - VNODE_START_NID] = *valp;
			valp++;
		}
		if (ch & 2) {
			spec->vnode_rswitch[nid - VNODE_START_NID] = *valp;
			valp++;
		}
		changed = ca0132_vnode_switch_set(kcontrol, ucontrol);
		goto exit;
	}

	/* PE */
	if (nid == PLAY_ENHANCEMENT) {
		spec->effects_switch[nid - EFFECT_START_NID] = *valp;
		changed = ca0132_pe_switch_set(codec);
		goto exit;
	}

	/* CrystalVoice */
	if (nid == CRYSTAL_VOICE) {
		spec->effects_switch[nid - EFFECT_START_NID] = *valp;
		changed = ca0132_cvoice_switch_set(codec);
		goto exit;
	}

	/* out and in effects */
	if (((nid >= OUT_EFFECT_START_NID) && (nid < OUT_EFFECT_END_NID)) ||
	    ((nid >= IN_EFFECT_START_NID) && (nid < IN_EFFECT_END_NID))) {
		spec->effects_switch[nid - EFFECT_START_NID] = *valp;
		changed = ca0132_effects_set(codec, nid, *valp);
		goto exit;
	}

	/* mic boost */
	if (nid == spec->input_pins[0]) {
		spec->cur_mic_boost = *valp;
		if (ca0132_use_alt_functions(spec)) {
			if (spec->in_enum_val != REAR_LINE_IN)
				changed = ca0132_mic_boost_set(codec, *valp);
		} else {
			/* Mic boost does not apply to Digital Mic */
			if (spec->cur_mic_type != DIGITAL_MIC)
				changed = ca0132_mic_boost_set(codec, *valp);
		}

		goto exit;
	}

	if (nid == ZXR_HEADPHONE_GAIN) {
		spec->zxr_gain_set = *valp;
		if (spec->cur_out_type == HEADPHONE_OUT)
			changed = zxr_headphone_gain_set(codec, *valp);
		else
			changed = 0;

		goto exit;
	}

exit:
	snd_hda_power_down(codec);
	return changed;
}