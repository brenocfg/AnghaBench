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
struct hda_input_mux {int num_items; } ;
struct hda_fixup {int dummy; } ;
struct hda_codec {struct alc_spec* spec; } ;
struct TYPE_2__ {int* imux_pins; int* cur_mux; struct hda_input_mux input_mux; } ;
struct alc_spec {TYPE_1__ gen; int /*<<< orphan*/  shutup; } ;

/* Variables and functions */
#define  HDA_FIXUP_ACT_PRE_PROBE 129 
#define  HDA_FIXUP_ACT_PROBE 128 
 int /*<<< orphan*/  PIN_VREFHIZ ; 
 int /*<<< orphan*/  alc_shutup_dell_xps13 ; 
 int /*<<< orphan*/  snd_hda_codec_set_pin_target (struct hda_codec*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alc_fixup_dell_xps13(struct hda_codec *codec,
				const struct hda_fixup *fix, int action)
{
	struct alc_spec *spec = codec->spec;
	struct hda_input_mux *imux = &spec->gen.input_mux;
	int i;

	switch (action) {
	case HDA_FIXUP_ACT_PRE_PROBE:
		/* mic pin 0x19 must be initialized with Vref Hi-Z, otherwise
		 * it causes a click noise at start up
		 */
		snd_hda_codec_set_pin_target(codec, 0x19, PIN_VREFHIZ);
		spec->shutup = alc_shutup_dell_xps13;
		break;
	case HDA_FIXUP_ACT_PROBE:
		/* Make the internal mic the default input source. */
		for (i = 0; i < imux->num_items; i++) {
			if (spec->gen.imux_pins[i] == 0x12) {
				spec->gen.cur_mux[0] = i;
				break;
			}
		}
		break;
	}
}