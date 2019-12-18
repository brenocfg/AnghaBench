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
struct TYPE_3__ {unsigned int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct auto_pin_cfg {scalar_t__ line_out_type; int /*<<< orphan*/  speaker_outs; int /*<<< orphan*/  hp_outs; int /*<<< orphan*/  line_outs; } ;
struct hda_gen_spec {unsigned int aamix_mode; int /*<<< orphan*/ * speaker_paths; int /*<<< orphan*/ * hp_paths; int /*<<< orphan*/ * out_paths; int /*<<< orphan*/ * aamix_out_paths; struct auto_pin_cfg autocfg; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 scalar_t__ AUTO_PIN_HP_OUT ; 
 scalar_t__ AUTO_PIN_SPEAKER_OUT ; 
 scalar_t__ has_aamix_out_paths (struct hda_gen_spec*) ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  update_aamix_paths (struct hda_codec*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  update_output_paths (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int loopback_mixing_put(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	struct hda_gen_spec *spec = codec->spec;
	const struct auto_pin_cfg *cfg = &spec->autocfg;
	unsigned int val = ucontrol->value.enumerated.item[0];

	if (val == spec->aamix_mode)
		return 0;
	spec->aamix_mode = val;
	if (has_aamix_out_paths(spec)) {
		update_aamix_paths(codec, val, spec->out_paths[0],
				   spec->aamix_out_paths[0],
				   cfg->line_out_type);
		update_aamix_paths(codec, val, spec->hp_paths[0],
				   spec->aamix_out_paths[1],
				   AUTO_PIN_HP_OUT);
		update_aamix_paths(codec, val, spec->speaker_paths[0],
				   spec->aamix_out_paths[2],
				   AUTO_PIN_SPEAKER_OUT);
	} else {
		update_output_paths(codec, cfg->line_outs, spec->out_paths);
		if (cfg->line_out_type != AUTO_PIN_HP_OUT)
			update_output_paths(codec, cfg->hp_outs, spec->hp_paths);
		if (cfg->line_out_type != AUTO_PIN_SPEAKER_OUT)
			update_output_paths(codec, cfg->speaker_outs,
					    spec->speaker_paths);
	}
	return 1;
}