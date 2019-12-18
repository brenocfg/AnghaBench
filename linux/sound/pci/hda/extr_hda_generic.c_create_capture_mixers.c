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
struct snd_kcontrol_new {int count; } ;
struct nid_path {int* ctls; } ;
struct hda_input_mux {int num_items; } ;
struct hda_gen_spec {int num_adc_nids; int multi_cap_vol; int /*<<< orphan*/ * imux_pins; int /*<<< orphan*/  auto_mic; scalar_t__ dyn_adc_switch; struct hda_input_mux input_mux; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HDA_INPUT ; 
 size_t NID_PATH_MUTE_CTL ; 
 size_t NID_PATH_VOL_CTL ; 
 int /*<<< orphan*/  cap_src_temp ; 
 int create_bind_cap_vol_ctl (struct hda_codec*,int,int,int) ; 
 int create_multi_cap_vol_ctl (struct hda_codec*) ; 
 int create_single_cap_vol_ctl (struct hda_codec*,int,int,int,int) ; 
 struct nid_path* get_input_path (struct hda_codec*,int,int) ; 
 scalar_t__ is_inv_dmic_pin (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_capvol_in_path (struct hda_codec*,struct nid_path*) ; 
 int /*<<< orphan*/  same_amp_caps (struct hda_codec*,int,int,int /*<<< orphan*/ ) ; 
 struct snd_kcontrol_new* snd_hda_gen_add_kctl (struct hda_gen_spec*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_capture_mixers(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	struct hda_input_mux *imux = &spec->input_mux;
	int i, n, nums, err;

	if (spec->dyn_adc_switch)
		nums = 1;
	else
		nums = spec->num_adc_nids;

	if (!spec->auto_mic && imux->num_items > 1) {
		struct snd_kcontrol_new *knew;
		const char *name;
		name = nums > 1 ? "Input Source" : "Capture Source";
		knew = snd_hda_gen_add_kctl(spec, name, &cap_src_temp);
		if (!knew)
			return -ENOMEM;
		knew->count = nums;
	}

	for (n = 0; n < nums; n++) {
		bool multi = false;
		bool multi_cap_vol = spec->multi_cap_vol;
		bool inv_dmic = false;
		int vol, sw;

		vol = sw = 0;
		for (i = 0; i < imux->num_items; i++) {
			struct nid_path *path;
			path = get_input_path(codec, n, i);
			if (!path)
				continue;
			parse_capvol_in_path(codec, path);
			if (!vol)
				vol = path->ctls[NID_PATH_VOL_CTL];
			else if (vol != path->ctls[NID_PATH_VOL_CTL]) {
				multi = true;
				if (!same_amp_caps(codec, vol,
				    path->ctls[NID_PATH_VOL_CTL], HDA_INPUT))
					multi_cap_vol = true;
			}
			if (!sw)
				sw = path->ctls[NID_PATH_MUTE_CTL];
			else if (sw != path->ctls[NID_PATH_MUTE_CTL]) {
				multi = true;
				if (!same_amp_caps(codec, sw,
				    path->ctls[NID_PATH_MUTE_CTL], HDA_INPUT))
					multi_cap_vol = true;
			}
			if (is_inv_dmic_pin(codec, spec->imux_pins[i]))
				inv_dmic = true;
		}

		if (!multi)
			err = create_single_cap_vol_ctl(codec, n, vol, sw,
							inv_dmic);
		else if (!multi_cap_vol && !inv_dmic)
			err = create_bind_cap_vol_ctl(codec, n, vol, sw);
		else
			err = create_multi_cap_vol_ctl(codec);
		if (err < 0)
			return err;
	}

	return 0;
}