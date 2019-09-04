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
struct hda_codec {int /*<<< orphan*/  patch_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  automute_hook; } ;
struct cs_spec {TYPE_1__ gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4210_VENDOR_NID ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  HDA_FIXUP_ACT_PROBE ; 
 int /*<<< orphan*/  cs4210_pinmux_init (struct hda_codec*) ; 
 int /*<<< orphan*/  cs421x_fixup_tbl ; 
 int /*<<< orphan*/  cs421x_fixups ; 
 int /*<<< orphan*/  cs421x_models ; 
 int cs421x_parse_auto_config (struct hda_codec*) ; 
 int /*<<< orphan*/  cs421x_patch_ops ; 
 struct cs_spec* cs_alloc_spec (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_automute ; 
 int /*<<< orphan*/  cs_free (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_apply_fixup (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_pick_fixup (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int patch_cs4210(struct hda_codec *codec)
{
	struct cs_spec *spec;
	int err;

	spec = cs_alloc_spec(codec, CS4210_VENDOR_NID);
	if (!spec)
		return -ENOMEM;

	codec->patch_ops = cs421x_patch_ops;
	spec->gen.automute_hook = cs_automute;

	snd_hda_pick_fixup(codec, cs421x_models, cs421x_fixup_tbl,
			   cs421x_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	/*
	    Update the GPIO/DMIC/SENSE_B pinmux before the configuration
	    is auto-parsed. If GPIO or SENSE_B is forced, DMIC input
	    is disabled.
	*/
	cs4210_pinmux_init(codec);

	err = cs421x_parse_auto_config(codec);
	if (err < 0)
		goto error;

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	return 0;

 error:
	cs_free(codec);
	return err;
}