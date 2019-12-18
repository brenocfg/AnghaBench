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
struct TYPE_2__ {scalar_t__ line_out_type; scalar_t__* hp_pins; scalar_t__* speaker_pins; scalar_t__* line_out_pins; } ;
struct hda_gen_spec {int* out_paths; int* hp_paths; int master_mute; int hp_jack_present; int line_jack_present; int speaker_muted; int* speaker_paths; int line_out_muted; TYPE_1__ autocfg; int /*<<< orphan*/  automute_lo; int /*<<< orphan*/  automute_speaker; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ AUTO_PIN_HP_OUT ; 
 scalar_t__ AUTO_PIN_SPEAKER_OUT ; 
 int /*<<< orphan*/  do_automute (struct hda_codec*,int /*<<< orphan*/ ,scalar_t__*,int*,int) ; 

void snd_hda_gen_update_outputs(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	int *paths;
	int on;

	/* Control HP pins/amps depending on master_mute state;
	 * in general, HP pins/amps control should be enabled in all cases,
	 * but currently set only for master_mute, just to be safe
	 */
	if (spec->autocfg.line_out_type == AUTO_PIN_HP_OUT)
		paths = spec->out_paths;
	else
		paths = spec->hp_paths;
	do_automute(codec, ARRAY_SIZE(spec->autocfg.hp_pins),
		    spec->autocfg.hp_pins, paths, spec->master_mute);

	if (!spec->automute_speaker)
		on = 0;
	else
		on = spec->hp_jack_present | spec->line_jack_present;
	on |= spec->master_mute;
	spec->speaker_muted = on;
	if (spec->autocfg.line_out_type == AUTO_PIN_SPEAKER_OUT)
		paths = spec->out_paths;
	else
		paths = spec->speaker_paths;
	do_automute(codec, ARRAY_SIZE(spec->autocfg.speaker_pins),
		    spec->autocfg.speaker_pins, paths, on);

	/* toggle line-out mutes if needed, too */
	/* if LO is a copy of either HP or Speaker, don't need to handle it */
	if (spec->autocfg.line_out_pins[0] == spec->autocfg.hp_pins[0] ||
	    spec->autocfg.line_out_pins[0] == spec->autocfg.speaker_pins[0])
		return;
	if (!spec->automute_lo)
		on = 0;
	else
		on = spec->hp_jack_present;
	on |= spec->master_mute;
	spec->line_out_muted = on;
	paths = spec->out_paths;
	do_automute(codec, ARRAY_SIZE(spec->autocfg.line_out_pins),
		    spec->autocfg.line_out_pins, paths, on);
}