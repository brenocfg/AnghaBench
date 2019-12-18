#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {scalar_t__ cur_out_type; scalar_t__ cur_mic_type; scalar_t__ in_enum_val; scalar_t__* effects_switch; } ;
typedef  scalar_t__ hda_nid_t ;
struct TYPE_2__ {int mid; int* reqs; } ;

/* Variables and functions */
 scalar_t__ CRYSTAL_VOICE ; 
 scalar_t__ DIGITAL_MIC ; 
 scalar_t__ EFFECT_START_NID ; 
 unsigned int FLOAT_ONE ; 
 unsigned int FLOAT_TWO ; 
 unsigned int FLOAT_ZERO ; 
 int IN_EFFECTS_COUNT ; 
 scalar_t__ IN_EFFECT_END_NID ; 
 scalar_t__ IN_EFFECT_START_NID ; 
 scalar_t__ NOISE_REDUCTION ; 
 int OUT_EFFECTS_COUNT ; 
 scalar_t__ OUT_EFFECT_END_NID ; 
 scalar_t__ OUT_EFFECT_START_NID ; 
 scalar_t__ PLAY_ENHANCEMENT ; 
 scalar_t__ REAR_LINE_IN ; 
 scalar_t__ SURROUND_OUT ; 
 scalar_t__ VOICE_FOCUS ; 
 scalar_t__ X_BASS ; 
 TYPE_1__* ca0132_effects ; 
 scalar_t__ ca0132_use_alt_functions (struct ca0132_spec*) ; 
 scalar_t__ ca0132_use_pci_mmio (struct ca0132_spec*) ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,scalar_t__,long) ; 
 int dspio_set_uint_param (struct hda_codec*,int,int,unsigned int) ; 

__attribute__((used)) static int ca0132_effects_set(struct hda_codec *codec, hda_nid_t nid, long val)
{
	struct ca0132_spec *spec = codec->spec;
	unsigned int on, tmp;
	int num_fx = OUT_EFFECTS_COUNT + IN_EFFECTS_COUNT;
	int err = 0;
	int idx = nid - EFFECT_START_NID;

	if ((idx < 0) || (idx >= num_fx))
		return 0; /* no changed */

	/* for out effect, qualify with PE */
	if ((nid >= OUT_EFFECT_START_NID) && (nid < OUT_EFFECT_END_NID)) {
		/* if PE if off, turn off out effects. */
		if (!spec->effects_switch[PLAY_ENHANCEMENT - EFFECT_START_NID])
			val = 0;
		if (spec->cur_out_type == SURROUND_OUT && nid == X_BASS)
			val = 0;
	}

	/* for in effect, qualify with CrystalVoice */
	if ((nid >= IN_EFFECT_START_NID) && (nid < IN_EFFECT_END_NID)) {
		/* if CrystalVoice if off, turn off in effects. */
		if (!spec->effects_switch[CRYSTAL_VOICE - EFFECT_START_NID])
			val = 0;

		/* Voice Focus applies to 2-ch Mic, Digital Mic */
		if ((nid == VOICE_FOCUS) && (spec->cur_mic_type != DIGITAL_MIC))
			val = 0;

		/* If Voice Focus on SBZ, set to two channel. */
		if ((nid == VOICE_FOCUS) && ca0132_use_pci_mmio(spec)
				&& (spec->cur_mic_type != REAR_LINE_IN)) {
			if (spec->effects_switch[CRYSTAL_VOICE -
						 EFFECT_START_NID]) {

				if (spec->effects_switch[VOICE_FOCUS -
							 EFFECT_START_NID]) {
					tmp = FLOAT_TWO;
					val = 1;
				} else
					tmp = FLOAT_ONE;

				dspio_set_uint_param(codec, 0x80, 0x00, tmp);
			}
		}
		/*
		 * For SBZ noise reduction, there's an extra command
		 * to module ID 0x47. No clue why.
		 */
		if ((nid == NOISE_REDUCTION) && ca0132_use_pci_mmio(spec)
				&& (spec->cur_mic_type != REAR_LINE_IN)) {
			if (spec->effects_switch[CRYSTAL_VOICE -
						 EFFECT_START_NID]) {
				if (spec->effects_switch[NOISE_REDUCTION -
							 EFFECT_START_NID])
					tmp = FLOAT_ONE;
				else
					tmp = FLOAT_ZERO;
			} else
				tmp = FLOAT_ZERO;

			dspio_set_uint_param(codec, 0x47, 0x00, tmp);
		}

		/* If rear line in disable effects. */
		if (ca0132_use_alt_functions(spec) &&
				spec->in_enum_val == REAR_LINE_IN)
			val = 0;
	}

	codec_dbg(codec, "ca0132_effect_set: nid=0x%x, val=%ld\n",
		    nid, val);

	on = (val == 0) ? FLOAT_ZERO : FLOAT_ONE;
	err = dspio_set_uint_param(codec, ca0132_effects[idx].mid,
				   ca0132_effects[idx].reqs[0], on);

	if (err < 0)
		return 0; /* no changed */

	return 1;
}