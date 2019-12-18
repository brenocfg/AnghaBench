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
struct auto_pin_cfg {scalar_t__ line_out_type; int speaker_outs; int line_outs; int hp_outs; scalar_t__* line_out_pins; scalar_t__* hp_pins; scalar_t__* speaker_pins; } ;
struct hda_gen_spec {int detect_hp; int detect_lo; int automute_lo_possible; int automute_speaker_possible; int automute_lo; int automute_speaker; scalar_t__ suppress_auto_mute; struct auto_pin_cfg autocfg; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 scalar_t__ AUTO_PIN_HP_OUT ; 
 scalar_t__ AUTO_PIN_LINE_OUT ; 
 scalar_t__ AUTO_PIN_SPEAKER_OUT ; 
 int add_automute_mode_enum (struct hda_codec*) ; 
 int /*<<< orphan*/  call_hp_automute ; 
 int /*<<< orphan*/  call_line_automute ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,scalar_t__) ; 
 int /*<<< orphan*/  is_jack_detectable (struct hda_codec*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  snd_hda_jack_detect_enable_callback (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_auto_mute_availability(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	struct auto_pin_cfg *cfg = &spec->autocfg;
	int present = 0;
	int i, err;

	if (spec->suppress_auto_mute)
		return 0;

	if (cfg->hp_pins[0])
		present++;
	if (cfg->line_out_pins[0])
		present++;
	if (cfg->speaker_pins[0])
		present++;
	if (present < 2) /* need two different output types */
		return 0;

	if (!cfg->speaker_pins[0] &&
	    cfg->line_out_type == AUTO_PIN_SPEAKER_OUT) {
		memcpy(cfg->speaker_pins, cfg->line_out_pins,
		       sizeof(cfg->speaker_pins));
		cfg->speaker_outs = cfg->line_outs;
	}

	if (!cfg->hp_pins[0] &&
	    cfg->line_out_type == AUTO_PIN_HP_OUT) {
		memcpy(cfg->hp_pins, cfg->line_out_pins,
		       sizeof(cfg->hp_pins));
		cfg->hp_outs = cfg->line_outs;
	}

	for (i = 0; i < cfg->hp_outs; i++) {
		hda_nid_t nid = cfg->hp_pins[i];
		if (!is_jack_detectable(codec, nid))
			continue;
		codec_dbg(codec, "Enable HP auto-muting on NID 0x%x\n", nid);
		snd_hda_jack_detect_enable_callback(codec, nid,
						    call_hp_automute);
		spec->detect_hp = 1;
	}

	if (cfg->line_out_type == AUTO_PIN_LINE_OUT && cfg->line_outs) {
		if (cfg->speaker_outs)
			for (i = 0; i < cfg->line_outs; i++) {
				hda_nid_t nid = cfg->line_out_pins[i];
				if (!is_jack_detectable(codec, nid))
					continue;
				codec_dbg(codec, "Enable Line-Out auto-muting on NID 0x%x\n", nid);
				snd_hda_jack_detect_enable_callback(codec, nid,
								    call_line_automute);
				spec->detect_lo = 1;
			}
		spec->automute_lo_possible = spec->detect_hp;
	}

	spec->automute_speaker_possible = cfg->speaker_outs &&
		(spec->detect_hp || spec->detect_lo);

	spec->automute_lo = spec->automute_lo_possible;
	spec->automute_speaker = spec->automute_speaker_possible;

	if (spec->automute_speaker_possible || spec->automute_lo_possible) {
		/* create a control for automute mode */
		err = add_automute_mode_enum(codec);
		if (err < 0)
			return err;
	}
	return 0;
}