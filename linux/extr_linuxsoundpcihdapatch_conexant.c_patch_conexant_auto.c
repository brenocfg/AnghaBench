#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int vendor_id; int subsystem_id; int /*<<< orphan*/  chip_name; } ;
struct hda_codec {int single_adc_amp; int pin_amp_workaround; int power_save_node; TYPE_4__* bus; TYPE_2__ core; int /*<<< orphan*/  patch_ops; struct conexant_spec* spec; } ;
struct TYPE_6__ {int /*<<< orphan*/  hook; } ;
struct TYPE_10__ {int own_eapd_ctl; int mixer_nid; int vmaster_mute_enum; int /*<<< orphan*/  autocfg; void* add_stereo_mix_input; TYPE_1__ vmaster_mute; } ;
struct conexant_spec {TYPE_5__ gen; int /*<<< orphan*/  parse_flags; scalar_t__ dynamic_eapd; } ;
struct TYPE_8__ {int sync_write; } ;
struct TYPE_9__ {int allow_bus_reset; TYPE_3__ core; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  HDA_FIXUP_ACT_PROBE ; 
 void* HDA_HINT_STEREO_MIX_AUTO ; 
 int /*<<< orphan*/  add_cx5051_fake_mutes (struct hda_codec*) ; 
 int /*<<< orphan*/  codec_info (struct hda_codec*,char*,...) ; 
 int /*<<< orphan*/  cx_auto_free (struct hda_codec*) ; 
 int cx_auto_parse_beep (struct hda_codec*) ; 
 int /*<<< orphan*/  cx_auto_parse_eapd (struct hda_codec*) ; 
 int /*<<< orphan*/  cx_auto_patch_ops ; 
 int /*<<< orphan*/  cx_auto_vmaster_hook ; 
 int /*<<< orphan*/  cxt5045_fixup_models ; 
 int /*<<< orphan*/  cxt5045_fixups ; 
 int /*<<< orphan*/  cxt5047_fixup_models ; 
 int /*<<< orphan*/  cxt5047_fixups ; 
 int /*<<< orphan*/  cxt5051_fixup_models ; 
 int /*<<< orphan*/  cxt5051_fixups ; 
 int /*<<< orphan*/  cxt5066_fixup_models ; 
 int /*<<< orphan*/  cxt5066_fixups ; 
 int /*<<< orphan*/  cxt_fixups ; 
 struct conexant_spec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_apply_fixup (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int snd_hda_gen_parse_auto_config (struct hda_codec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hda_gen_spec_init (TYPE_5__*) ; 
 int snd_hda_parse_pin_defcfg (struct hda_codec*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_pick_fixup (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int patch_conexant_auto(struct hda_codec *codec)
{
	struct conexant_spec *spec;
	int err;

	codec_info(codec, "%s: BIOS auto-probing.\n", codec->core.chip_name);

	spec = kzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec)
		return -ENOMEM;
	snd_hda_gen_spec_init(&spec->gen);
	codec->spec = spec;
	codec->patch_ops = cx_auto_patch_ops;

	cx_auto_parse_eapd(codec);
	spec->gen.own_eapd_ctl = 1;
	if (spec->dynamic_eapd)
		spec->gen.vmaster_mute.hook = cx_auto_vmaster_hook;

	switch (codec->core.vendor_id) {
	case 0x14f15045:
		codec->single_adc_amp = 1;
		spec->gen.mixer_nid = 0x17;
		spec->gen.add_stereo_mix_input = HDA_HINT_STEREO_MIX_AUTO;
		snd_hda_pick_fixup(codec, cxt5045_fixup_models,
				   cxt5045_fixups, cxt_fixups);
		break;
	case 0x14f15047:
		codec->pin_amp_workaround = 1;
		spec->gen.mixer_nid = 0x19;
		spec->gen.add_stereo_mix_input = HDA_HINT_STEREO_MIX_AUTO;
		snd_hda_pick_fixup(codec, cxt5047_fixup_models,
				   cxt5047_fixups, cxt_fixups);
		break;
	case 0x14f15051:
		add_cx5051_fake_mutes(codec);
		codec->pin_amp_workaround = 1;
		snd_hda_pick_fixup(codec, cxt5051_fixup_models,
				   cxt5051_fixups, cxt_fixups);
		break;
	case 0x14f150f2:
		codec->power_save_node = 1;
		/* Fall through */
	default:
		codec->pin_amp_workaround = 1;
		snd_hda_pick_fixup(codec, cxt5066_fixup_models,
				   cxt5066_fixups, cxt_fixups);
		break;
	}

	/* Show mute-led control only on HP laptops
	 * This is a sort of white-list: on HP laptops, EAPD corresponds
	 * only to the mute-LED without actualy amp function.  Meanwhile,
	 * others may use EAPD really as an amp switch, so it might be
	 * not good to expose it blindly.
	 */
	switch (codec->core.subsystem_id >> 16) {
	case 0x103c:
		spec->gen.vmaster_mute_enum = 1;
		break;
	}

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	err = snd_hda_parse_pin_defcfg(codec, &spec->gen.autocfg, NULL,
				       spec->parse_flags);
	if (err < 0)
		goto error;

	err = snd_hda_gen_parse_auto_config(codec, &spec->gen.autocfg);
	if (err < 0)
		goto error;

	err = cx_auto_parse_beep(codec);
	if (err < 0)
		goto error;

	/* Some laptops with Conexant chips show stalls in S3 resume,
	 * which falls into the single-cmd mode.
	 * Better to make reset, then.
	 */
	if (!codec->bus->core.sync_write) {
		codec_info(codec,
			   "Enable sync_write for stable communication\n");
		codec->bus->core.sync_write = 1;
		codec->bus->allow_bus_reset = 1;
	}

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	return 0;

 error:
	cx_auto_free(codec);
	return err;
}