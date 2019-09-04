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
struct TYPE_2__ {scalar_t__ power_down_unused; int /*<<< orphan*/  autocfg; int /*<<< orphan*/ * extra_out_badness; int /*<<< orphan*/ * main_out_badness; } ;
struct via_spec {TYPE_1__ gen; } ;
struct hda_codec {scalar_t__ power_save_node; struct via_spec* spec; } ;

/* Variables and functions */
 int ENOMEM ; 
 int auto_parse_beep (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_gen_add_kctl (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int snd_hda_gen_parse_auto_config (struct hda_codec*,int /*<<< orphan*/ *) ; 
 int snd_hda_parse_pin_defcfg (struct hda_codec*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  via_extra_out_badness ; 
 int /*<<< orphan*/  via_main_out_badness ; 
 int /*<<< orphan*/  via_pin_power_ctl_enum ; 

__attribute__((used)) static int via_parse_auto_config(struct hda_codec *codec)
{
	struct via_spec *spec = codec->spec;
	int err;

	spec->gen.main_out_badness = &via_main_out_badness;
	spec->gen.extra_out_badness = &via_extra_out_badness;

	err = snd_hda_parse_pin_defcfg(codec, &spec->gen.autocfg, NULL, 0);
	if (err < 0)
		return err;

	err = snd_hda_gen_parse_auto_config(codec, &spec->gen.autocfg);
	if (err < 0)
		return err;

	err = auto_parse_beep(codec);
	if (err < 0)
		return err;

	if (!snd_hda_gen_add_kctl(&spec->gen, NULL, &via_pin_power_ctl_enum))
		return -ENOMEM;

	/* disable widget PM at start for compatibility */
	codec->power_save_node = 0;
	spec->gen.power_down_unused = 0;
	return 0;
}