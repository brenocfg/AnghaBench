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
struct TYPE_4__ {scalar_t__ line_out_type; int line_outs; int speaker_outs; int /*<<< orphan*/ * speaker_pins; int /*<<< orphan*/ * line_out_pins; } ;
struct TYPE_3__ {TYPE_2__ autocfg; } ;
struct sigmatel_spec {TYPE_1__ gen; } ;
struct hda_codec {struct sigmatel_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 scalar_t__ AUTO_PIN_SPEAKER_OUT ; 
 scalar_t__ INPUT_PIN_ATTR_INT ; 
 unsigned int snd_hda_codec_get_pincfg (struct hda_codec*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_hda_get_input_pin_attr (unsigned int) ; 

__attribute__((used)) static bool has_builtin_speaker(struct hda_codec *codec)
{
	struct sigmatel_spec *spec = codec->spec;
	hda_nid_t *nid_pin;
	int nids, i;

	if (spec->gen.autocfg.line_out_type == AUTO_PIN_SPEAKER_OUT) {
		nid_pin = spec->gen.autocfg.line_out_pins;
		nids = spec->gen.autocfg.line_outs;
	} else {
		nid_pin = spec->gen.autocfg.speaker_pins;
		nids = spec->gen.autocfg.speaker_outs;
	}

	for (i = 0; i < nids; i++) {
		unsigned int def_conf = snd_hda_codec_get_pincfg(codec, nid_pin[i]);
		if (snd_hda_get_input_pin_attr(def_conf) == INPUT_PIN_ATTR_INT)
			return true;
	}
	return false;
}