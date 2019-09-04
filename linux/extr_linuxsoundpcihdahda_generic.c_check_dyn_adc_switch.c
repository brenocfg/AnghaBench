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
struct hda_input_mux {int num_items; } ;
struct hda_gen_spec {int num_adc_nids; int* dyn_adc_idx; int dyn_adc_switch; scalar_t__ multi_cap_vol; scalar_t__ hp_mic; scalar_t__** input_paths; int /*<<< orphan*/ * adc_nids; struct hda_input_mux input_mux; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*) ; 
 int /*<<< orphan*/  invalidate_nid_path (struct hda_codec*,scalar_t__) ; 

__attribute__((used)) static int check_dyn_adc_switch(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	struct hda_input_mux *imux = &spec->input_mux;
	unsigned int ok_bits;
	int i, n, nums;

	nums = 0;
	ok_bits = 0;
	for (n = 0; n < spec->num_adc_nids; n++) {
		for (i = 0; i < imux->num_items; i++) {
			if (!spec->input_paths[i][n])
				break;
		}
		if (i >= imux->num_items) {
			ok_bits |= (1 << n);
			nums++;
		}
	}

	if (!ok_bits) {
		/* check whether ADC-switch is possible */
		for (i = 0; i < imux->num_items; i++) {
			for (n = 0; n < spec->num_adc_nids; n++) {
				if (spec->input_paths[i][n]) {
					spec->dyn_adc_idx[i] = n;
					break;
				}
			}
		}

		codec_dbg(codec, "enabling ADC switching\n");
		spec->dyn_adc_switch = 1;
	} else if (nums != spec->num_adc_nids) {
		/* shrink the invalid adcs and input paths */
		nums = 0;
		for (n = 0; n < spec->num_adc_nids; n++) {
			if (!(ok_bits & (1 << n)))
				continue;
			if (n != nums) {
				spec->adc_nids[nums] = spec->adc_nids[n];
				for (i = 0; i < imux->num_items; i++) {
					invalidate_nid_path(codec,
						spec->input_paths[i][nums]);
					spec->input_paths[i][nums] =
						spec->input_paths[i][n];
					spec->input_paths[i][n] = 0;
				}
			}
			nums++;
		}
		spec->num_adc_nids = nums;
	}

	if (imux->num_items == 1 ||
	    (imux->num_items == 2 && spec->hp_mic)) {
		codec_dbg(codec, "reducing to a single ADC\n");
		spec->num_adc_nids = 1; /* reduce to a single ADC */
	}

	/* single index for individual volumes ctls */
	if (!spec->dyn_adc_switch && spec->multi_cap_vol)
		spec->num_adc_nids = 1;

	return 0;
}