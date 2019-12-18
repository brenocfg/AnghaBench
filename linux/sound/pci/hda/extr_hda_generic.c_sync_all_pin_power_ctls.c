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
struct auto_pin_cfg {int line_outs; scalar_t__ line_out_type; int hp_outs; int speaker_outs; int num_inputs; TYPE_1__* inputs; int /*<<< orphan*/ * speaker_pins; int /*<<< orphan*/ * hp_pins; int /*<<< orphan*/ * line_out_pins; } ;
struct hda_gen_spec {struct auto_pin_cfg autocfg; } ;
struct hda_codec {int /*<<< orphan*/  power_save_node; struct hda_gen_spec* spec; } ;
struct TYPE_2__ {int /*<<< orphan*/  pin; } ;

/* Variables and functions */
 scalar_t__ AUTO_PIN_HP_OUT ; 
 scalar_t__ AUTO_PIN_SPEAKER_OUT ; 
 int /*<<< orphan*/  sync_pin_power_ctls (struct hda_codec*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sync_all_pin_power_ctls(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	struct auto_pin_cfg *cfg = &spec->autocfg;
	int i;

	if (!codec->power_save_node)
		return;
	sync_pin_power_ctls(codec, cfg->line_outs, cfg->line_out_pins);
	if (cfg->line_out_type != AUTO_PIN_HP_OUT)
		sync_pin_power_ctls(codec, cfg->hp_outs, cfg->hp_pins);
	if (cfg->line_out_type != AUTO_PIN_SPEAKER_OUT)
		sync_pin_power_ctls(codec, cfg->speaker_outs, cfg->speaker_pins);
	for (i = 0; i < cfg->num_inputs; i++)
		sync_pin_power_ctls(codec, 1, &cfg->inputs[i].pin);
}