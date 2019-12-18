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
 unsigned int FLOAT_ONE ; 
 unsigned int FLOAT_TWO ; 
 unsigned int FLOAT_ZERO ; 
 int IN_EFFECTS_COUNT ; 
 int OUT_EFFECTS_COUNT ; 
 TYPE_1__* ca0132_effects ; 
 int /*<<< orphan*/  dspio_set_uint_param (struct hda_codec*,int,int,unsigned int) ; 

__attribute__((used)) static void ca0132_setup_defaults(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;
	unsigned int tmp;
	int num_fx;
	int idx, i;

	if (spec->dsp_state != DSP_DOWNLOADED)
		return;

	/* out, in effects + voicefx */
	num_fx = OUT_EFFECTS_COUNT + IN_EFFECTS_COUNT + 1;
	for (idx = 0; idx < num_fx; idx++) {
		for (i = 0; i <= ca0132_effects[idx].params; i++) {
			dspio_set_uint_param(codec, ca0132_effects[idx].mid,
					     ca0132_effects[idx].reqs[i],
					     ca0132_effects[idx].def_vals[i]);
		}
	}

	/*remove DSP headroom*/
	tmp = FLOAT_ZERO;
	dspio_set_uint_param(codec, 0x96, 0x3C, tmp);

	/*set speaker EQ bypass attenuation*/
	dspio_set_uint_param(codec, 0x8f, 0x01, tmp);

	/* set AMic1 and AMic2 as mono mic */
	tmp = FLOAT_ONE;
	dspio_set_uint_param(codec, 0x80, 0x00, tmp);
	dspio_set_uint_param(codec, 0x80, 0x01, tmp);

	/* set AMic1 as CrystalVoice input */
	tmp = FLOAT_ONE;
	dspio_set_uint_param(codec, 0x80, 0x05, tmp);

	/* set WUH source */
	tmp = FLOAT_TWO;
	dspio_set_uint_param(codec, 0x31, 0x00, tmp);
}