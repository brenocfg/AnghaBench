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
struct auto_pin_cfg {scalar_t__ line_out_type; int /*<<< orphan*/  speaker_pins; int /*<<< orphan*/  speaker_outs; int /*<<< orphan*/  hp_pins; int /*<<< orphan*/  hp_outs; int /*<<< orphan*/  line_out_pins; int /*<<< orphan*/  line_outs; } ;
struct hda_gen_spec {int /*<<< orphan*/  beep_nid; struct auto_pin_cfg autocfg; } ;
struct hda_codec {int /*<<< orphan*/  power_save_node; struct hda_gen_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 scalar_t__ AUTO_PIN_HP_OUT ; 
 scalar_t__ AUTO_PIN_SPEAKER_OUT ; 
 int add_fake_paths (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_fake_beep_paths(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	struct auto_pin_cfg *cfg = &spec->autocfg;
	hda_nid_t nid = spec->beep_nid;
	int err;

	if (!codec->power_save_node || !nid)
		return 0;
	err = add_fake_paths(codec, nid, cfg->line_outs, cfg->line_out_pins);
	if (err < 0)
		return err;
	if (cfg->line_out_type != AUTO_PIN_HP_OUT) {
		err = add_fake_paths(codec, nid, cfg->hp_outs, cfg->hp_pins);
		if (err < 0)
			return err;
	}
	if (cfg->line_out_type != AUTO_PIN_SPEAKER_OUT) {
		err = add_fake_paths(codec, nid, cfg->speaker_outs,
				     cfg->speaker_pins);
		if (err < 0)
			return err;
	}
	return 0;
}