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
struct TYPE_2__ {int /*<<< orphan*/  line_out_type; } ;
struct hda_gen_spec {int /*<<< orphan*/ * aamix_out_paths; int /*<<< orphan*/ * speaker_paths; int /*<<< orphan*/  aamix_mode; int /*<<< orphan*/ * hp_paths; TYPE_1__ autocfg; int /*<<< orphan*/ * out_paths; int /*<<< orphan*/  have_aamix_ctl; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_PIN_HP_OUT ; 
 int /*<<< orphan*/  AUTO_PIN_SPEAKER_OUT ; 
 int /*<<< orphan*/  has_aamix_out_paths (struct hda_gen_spec*) ; 
 int /*<<< orphan*/  update_aamix_paths (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_aamix_paths(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;

	if (!spec->have_aamix_ctl)
		return;
	if (!has_aamix_out_paths(spec))
		return;
	update_aamix_paths(codec, spec->aamix_mode, spec->out_paths[0],
			   spec->aamix_out_paths[0],
			   spec->autocfg.line_out_type);
	update_aamix_paths(codec, spec->aamix_mode, spec->hp_paths[0],
			   spec->aamix_out_paths[1],
			   AUTO_PIN_HP_OUT);
	update_aamix_paths(codec, spec->aamix_mode, spec->speaker_paths[0],
			   spec->aamix_out_paths[2],
			   AUTO_PIN_SPEAKER_OUT);
}