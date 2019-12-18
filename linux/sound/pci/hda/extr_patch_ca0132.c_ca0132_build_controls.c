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
struct hda_codec {struct ca0132_spec* spec; } ;
struct TYPE_3__ {int /*<<< orphan*/  sw_kctl; } ;
struct ca0132_spec {int num_mixers; scalar_t__ dig_in; int /*<<< orphan*/  multiout; scalar_t__ dig_out; int /*<<< orphan*/  autocfg; TYPE_1__ vmaster_mute; int /*<<< orphan*/  tlv; int /*<<< orphan*/ * dacs; int /*<<< orphan*/ * mixers; } ;
struct TYPE_4__ {char* name; int direct; int /*<<< orphan*/  nid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYSTAL_VOICE ; 
 int ECHO_CANCELLATION ; 
 int EFX_DIR_OUT ; 
 int /*<<< orphan*/  HDA_OUTPUT ; 
 int IN_EFFECTS_COUNT ; 
 int IN_EFFECT_START_NID ; 
 int OUT_EFFECTS_COUNT ; 
 int /*<<< orphan*/  PLAY_ENHANCEMENT ; 
 scalar_t__ QUIRK_AE5 ; 
 scalar_t__ QUIRK_ZXR ; 
 int /*<<< orphan*/  XBASS_XOVER ; 
 int __snd_hda_add_vmaster (struct hda_codec*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int add_ca0132_alt_eq_presets (struct hda_codec*) ; 
 int add_fx_switch (struct hda_codec*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  add_tuning_ctls (struct hda_codec*) ; 
 int add_voicefx (struct hda_codec*) ; 
 int ae5_add_headphone_gain_enum (struct hda_codec*) ; 
 int ae5_add_sound_filter_enum (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0132_alt_add_chmap_ctls (struct hda_codec*) ; 
 int ca0132_alt_add_effect_slider (struct hda_codec*,int /*<<< orphan*/ ,char*,int) ; 
 int ca0132_alt_add_input_enum (struct hda_codec*) ; 
 int ca0132_alt_add_mic_boost_enum (struct hda_codec*) ; 
 int ca0132_alt_add_output_enum (struct hda_codec*) ; 
 int ca0132_alt_add_svm_enum (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0132_alt_slave_pfxs ; 
 TYPE_2__* ca0132_effects ; 
 scalar_t__ ca0132_quirk (struct ca0132_spec*) ; 
 scalar_t__ ca0132_use_alt_controls (struct ca0132_spec*) ; 
 scalar_t__ ca0132_use_alt_functions (struct ca0132_spec*) ; 
 scalar_t__ ca0132_use_pci_mmio (struct ca0132_spec*) ; 
 int snd_hda_add_new_ctls (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_add_vmaster (struct hda_codec*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int snd_hda_create_spdif_in_ctls (struct hda_codec*,scalar_t__) ; 
 int snd_hda_create_spdif_out_ctls (struct hda_codec*,scalar_t__,scalar_t__) ; 
 int snd_hda_create_spdif_share_sw (struct hda_codec*,int /*<<< orphan*/ *) ; 
 int snd_hda_jack_add_kctls (struct hda_codec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hda_set_vmaster_tlv (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zxr_add_headphone_gain_switch (struct hda_codec*) ; 

__attribute__((used)) static int ca0132_build_controls(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;
	int i, num_fx, num_sliders;
	int err = 0;

	/* Add Mixer controls */
	for (i = 0; i < spec->num_mixers; i++) {
		err = snd_hda_add_new_ctls(codec, spec->mixers[i]);
		if (err < 0)
			return err;
	}
	/* Setup vmaster with surround slaves for desktop ca0132 devices */
	if (ca0132_use_alt_functions(spec)) {
		snd_hda_set_vmaster_tlv(codec, spec->dacs[0], HDA_OUTPUT,
					spec->tlv);
		snd_hda_add_vmaster(codec, "Master Playback Volume",
					spec->tlv, ca0132_alt_slave_pfxs,
					"Playback Volume");
		err = __snd_hda_add_vmaster(codec, "Master Playback Switch",
					    NULL, ca0132_alt_slave_pfxs,
					    "Playback Switch",
					    true, &spec->vmaster_mute.sw_kctl);
		if (err < 0)
			return err;
	}

	/* Add in and out effects controls.
	 * VoiceFX, PE and CrystalVoice are added separately.
	 */
	num_fx = OUT_EFFECTS_COUNT + IN_EFFECTS_COUNT;
	for (i = 0; i < num_fx; i++) {
		/* Desktop cards break if Echo Cancellation is used. */
		if (ca0132_use_pci_mmio(spec)) {
			if (i == (ECHO_CANCELLATION - IN_EFFECT_START_NID +
						OUT_EFFECTS_COUNT))
				continue;
		}

		err = add_fx_switch(codec, ca0132_effects[i].nid,
				    ca0132_effects[i].name,
				    ca0132_effects[i].direct);
		if (err < 0)
			return err;
	}
	/*
	 * If codec has use_alt_controls set to true, add effect level sliders,
	 * EQ presets, and Smart Volume presets. Also, change names to add FX
	 * prefix, and change PlayEnhancement and CrystalVoice to match.
	 */
	if (ca0132_use_alt_controls(spec)) {
		err = ca0132_alt_add_svm_enum(codec);
		if (err < 0)
			return err;

		err = add_ca0132_alt_eq_presets(codec);
		if (err < 0)
			return err;

		err = add_fx_switch(codec, PLAY_ENHANCEMENT,
					"Enable OutFX", 0);
		if (err < 0)
			return err;

		err = add_fx_switch(codec, CRYSTAL_VOICE,
					"Enable InFX", 1);
		if (err < 0)
			return err;

		num_sliders = OUT_EFFECTS_COUNT - 1;
		for (i = 0; i < num_sliders; i++) {
			err = ca0132_alt_add_effect_slider(codec,
					    ca0132_effects[i].nid,
					    ca0132_effects[i].name,
					    ca0132_effects[i].direct);
			if (err < 0)
				return err;
		}

		err = ca0132_alt_add_effect_slider(codec, XBASS_XOVER,
					"X-Bass Crossover", EFX_DIR_OUT);

		if (err < 0)
			return err;
	} else {
		err = add_fx_switch(codec, PLAY_ENHANCEMENT,
					"PlayEnhancement", 0);
		if (err < 0)
			return err;

		err = add_fx_switch(codec, CRYSTAL_VOICE,
					"CrystalVoice", 1);
		if (err < 0)
			return err;
	}
	err = add_voicefx(codec);
	if (err < 0)
		return err;

	/*
	 * If the codec uses alt_functions, you need the enumerated controls
	 * to select the new outputs and inputs, plus add the new mic boost
	 * setting control.
	 */
	if (ca0132_use_alt_functions(spec)) {
		err = ca0132_alt_add_output_enum(codec);
		if (err < 0)
			return err;
		err = ca0132_alt_add_mic_boost_enum(codec);
		if (err < 0)
			return err;
		/*
		 * ZxR only has microphone input, there is no front panel
		 * header on the card, and aux-in is handled by the DBPro board.
		 */
		if (ca0132_quirk(spec) != QUIRK_ZXR) {
			err = ca0132_alt_add_input_enum(codec);
			if (err < 0)
				return err;
		}
	}

	if (ca0132_quirk(spec) == QUIRK_AE5) {
		err = ae5_add_headphone_gain_enum(codec);
		if (err < 0)
			return err;
		err = ae5_add_sound_filter_enum(codec);
		if (err < 0)
			return err;
	}

	if (ca0132_quirk(spec) == QUIRK_ZXR) {
		err = zxr_add_headphone_gain_switch(codec);
		if (err < 0)
			return err;
	}
#ifdef ENABLE_TUNING_CONTROLS
	add_tuning_ctls(codec);
#endif

	err = snd_hda_jack_add_kctls(codec, &spec->autocfg);
	if (err < 0)
		return err;

	if (spec->dig_out) {
		err = snd_hda_create_spdif_out_ctls(codec, spec->dig_out,
						    spec->dig_out);
		if (err < 0)
			return err;
		err = snd_hda_create_spdif_share_sw(codec, &spec->multiout);
		if (err < 0)
			return err;
		/* spec->multiout.share_spdif = 1; */
	}

	if (spec->dig_in) {
		err = snd_hda_create_spdif_in_ctls(codec, spec->dig_in);
		if (err < 0)
			return err;
	}

	if (ca0132_use_alt_functions(spec))
		ca0132_alt_add_chmap_ctls(codec);

	return 0;
}