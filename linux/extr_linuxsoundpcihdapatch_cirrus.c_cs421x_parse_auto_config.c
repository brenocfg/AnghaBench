#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hda_codec {struct cs_spec* spec; } ;
struct TYPE_4__ {scalar_t__ speaker_outs; } ;
struct TYPE_5__ {TYPE_1__ autocfg; } ;
struct cs_spec {scalar_t__ vendor_nid; TYPE_3__ gen; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CS4210_DAC_NID ; 
 scalar_t__ CS4210_VENDOR_NID ; 
 int ENOMEM ; 
 int /*<<< orphan*/  cs421x_speaker_boost_ctl ; 
 int /*<<< orphan*/  fix_volume_caps (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_cs421x_digital (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_gen_add_kctl (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int snd_hda_gen_parse_auto_config (struct hda_codec*,TYPE_1__*) ; 
 int snd_hda_parse_pin_defcfg (struct hda_codec*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs421x_parse_auto_config(struct hda_codec *codec)
{
	struct cs_spec *spec = codec->spec;
	hda_nid_t dac = CS4210_DAC_NID;
	int err;

	fix_volume_caps(codec, dac);

	err = snd_hda_parse_pin_defcfg(codec, &spec->gen.autocfg, NULL, 0);
	if (err < 0)
		return err;

	err = snd_hda_gen_parse_auto_config(codec, &spec->gen.autocfg);
	if (err < 0)
		return err;

	parse_cs421x_digital(codec);

	if (spec->gen.autocfg.speaker_outs &&
	    spec->vendor_nid == CS4210_VENDOR_NID) {
		if (!snd_hda_gen_add_kctl(&spec->gen, NULL,
					  &cs421x_speaker_boost_ctl))
			return -ENOMEM;
	}

	return 0;
}