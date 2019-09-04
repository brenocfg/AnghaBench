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
struct TYPE_2__ {unsigned long long out_vol_mask; int /*<<< orphan*/  automute_hook; } ;
struct cs_spec {TYPE_1__ gen; } ;

/* Variables and functions */
 int AC_WCAP_STEREO ; 
 int /*<<< orphan*/  CS4208_VENDOR_NID ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  HDA_FIXUP_ACT_PROBE ; 
 int /*<<< orphan*/  cs4208_fix_amp_caps (struct hda_codec*,int) ; 
 int /*<<< orphan*/  cs4208_fixup_tbl ; 
 int /*<<< orphan*/  cs4208_fixups ; 
 int /*<<< orphan*/  cs4208_models ; 
 struct cs_spec* cs_alloc_spec (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_automute ; 
 int /*<<< orphan*/  cs_free (struct hda_codec*) ; 
 int cs_parse_auto_config (struct hda_codec*) ; 
 int /*<<< orphan*/  cs_patch_ops ; 
 int get_wcaps (struct hda_codec*,int) ; 
 int /*<<< orphan*/  snd_hda_apply_fixup (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_override_wcaps (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  snd_hda_pick_fixup (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int patch_cs4208(struct hda_codec *codec)
{
	struct cs_spec *spec;
	int err;

	spec = cs_alloc_spec(codec, CS4208_VENDOR_NID);
	if (!spec)
		return -ENOMEM;

	codec->patch_ops = cs_patch_ops;
	spec->gen.automute_hook = cs_automute;
	/* exclude NID 0x10 (HP) from output volumes due to different steps */
	spec->gen.out_vol_mask = 1ULL << 0x10;

	snd_hda_pick_fixup(codec, cs4208_models, cs4208_fixup_tbl,
			   cs4208_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	snd_hda_override_wcaps(codec, 0x18,
			       get_wcaps(codec, 0x18) | AC_WCAP_STEREO);
	cs4208_fix_amp_caps(codec, 0x18);
	cs4208_fix_amp_caps(codec, 0x1b);
	cs4208_fix_amp_caps(codec, 0x1c);

	err = cs_parse_auto_config(codec);
	if (err < 0)
		goto error;

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	return 0;

 error:
	cs_free(codec);
	return err;
}