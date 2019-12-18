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
struct hda_input_mux {int num_items; TYPE_1__* items; } ;
struct TYPE_4__ {int num_inputs; } ;
struct hda_gen_spec {int /*<<< orphan*/ * input_label_idxs; int /*<<< orphan*/ * input_labels; int /*<<< orphan*/ * imux_pins; TYPE_2__ autocfg; struct hda_input_mux input_mux; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
struct TYPE_3__ {int index; } ;

/* Variables and functions */
 int add_single_cap_ctl (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_first_cap_ctl (struct hda_codec*,int,int) ; 
 int is_inv_dmic_pin (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_multi_cap_vol_ctl(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	struct hda_input_mux *imux = &spec->input_mux;
	int i, err, type;

	for (i = 0; i < imux->num_items; i++) {
		bool inv_dmic;
		int idx;

		idx = imux->items[i].index;
		if (idx >= spec->autocfg.num_inputs)
			continue;
		inv_dmic = is_inv_dmic_pin(codec, spec->imux_pins[i]);

		for (type = 0; type < 2; type++) {
			err = add_single_cap_ctl(codec,
						 spec->input_labels[idx],
						 spec->input_label_idxs[idx],
						 type,
						 get_first_cap_ctl(codec, i, type),
						 inv_dmic);
			if (err < 0)
				return err;
		}
	}
	return 0;
}