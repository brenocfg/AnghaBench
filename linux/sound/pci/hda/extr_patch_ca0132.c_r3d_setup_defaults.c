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
struct ca0132_spec {scalar_t__ dsp_state; } ;
struct TYPE_2__ {int params; int mid; int* reqs; unsigned int* def_vals; } ;

/* Variables and functions */
 scalar_t__ DSP_DOWNLOADED ; 
 unsigned int FLOAT_TWO ; 
 unsigned int FLOAT_ZERO ; 
 int IN_EFFECTS_COUNT ; 
 int /*<<< orphan*/  MEM_CONNID_WUH ; 
 int OUT_EFFECTS_COUNT ; 
 scalar_t__ QUIRK_R3DI ; 
 int /*<<< orphan*/  R3DI_DSP_DOWNLOADED ; 
 int /*<<< orphan*/  SR_48_000 ; 
 int /*<<< orphan*/  ca0132_alt_dsp_scp_startup (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0132_alt_init_analog_mics (struct hda_codec*) ; 
 TYPE_1__* ca0132_effects ; 
 scalar_t__ ca0132_quirk (struct ca0132_spec*) ; 
 int /*<<< orphan*/  chipio_set_conn_rate (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dspio_set_uint_param (struct hda_codec*,int,int,unsigned int) ; 
 int /*<<< orphan*/  r3di_gpio_dsp_status_set (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r3d_setup_defaults(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;
	unsigned int tmp;
	int num_fx;
	int idx, i;

	if (spec->dsp_state != DSP_DOWNLOADED)
		return;

	ca0132_alt_dsp_scp_startup(codec);
	ca0132_alt_init_analog_mics(codec);

	/*remove DSP headroom*/
	tmp = FLOAT_ZERO;
	dspio_set_uint_param(codec, 0x96, 0x3C, tmp);

	/* set WUH source */
	tmp = FLOAT_TWO;
	dspio_set_uint_param(codec, 0x31, 0x00, tmp);
	chipio_set_conn_rate(codec, MEM_CONNID_WUH, SR_48_000);

	/* Set speaker source? */
	dspio_set_uint_param(codec, 0x32, 0x00, tmp);

	if (ca0132_quirk(spec) == QUIRK_R3DI)
		r3di_gpio_dsp_status_set(codec, R3DI_DSP_DOWNLOADED);

	/* Setup effect defaults */
	num_fx = OUT_EFFECTS_COUNT + IN_EFFECTS_COUNT + 1;
	for (idx = 0; idx < num_fx; idx++) {
		for (i = 0; i <= ca0132_effects[idx].params; i++) {
			dspio_set_uint_param(codec,
					ca0132_effects[idx].mid,
					ca0132_effects[idx].reqs[i],
					ca0132_effects[idx].def_vals[i]);
		}
	}
}