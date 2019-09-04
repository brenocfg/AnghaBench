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
struct TYPE_2__ {int mixer_nid; } ;
struct via_spec {scalar_t__ codec_type; TYPE_1__ gen; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HDA_FIXUP_ACT_PRE_PROBE ; 
 scalar_t__ VT1802 ; 
 int /*<<< orphan*/  add_secret_dac_path (struct hda_codec*) ; 
 int /*<<< orphan*/  fix_vt1802_connections (struct hda_codec*) ; 
 int /*<<< orphan*/  override_mic_boost (struct hda_codec*,int,int /*<<< orphan*/ ,int,int) ; 
 int snd_hda_add_verbs (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_apply_fixup (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_pick_fixup (struct hda_codec*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  via_fixups ; 
 int /*<<< orphan*/  via_free (struct hda_codec*) ; 
 struct via_spec* via_new_spec (struct hda_codec*) ; 
 int via_parse_auto_config (struct hda_codec*) ; 
 int /*<<< orphan*/  vt1802_init_verbs ; 
 int /*<<< orphan*/  vt2002P_init_verbs ; 
 int /*<<< orphan*/  vt2002p_fixups ; 

__attribute__((used)) static int patch_vt2002P(struct hda_codec *codec)
{
	struct via_spec *spec;
	int err;

	/* create a codec specific record */
	spec = via_new_spec(codec);
	if (spec == NULL)
		return -ENOMEM;

	spec->gen.mixer_nid = 0x21;
	override_mic_boost(codec, 0x2b, 0, 3, 40);
	override_mic_boost(codec, 0x29, 0, 3, 40);
	if (spec->codec_type == VT1802)
		fix_vt1802_connections(codec);
	add_secret_dac_path(codec);

	snd_hda_pick_fixup(codec, NULL, vt2002p_fixups, via_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	if (spec->codec_type == VT1802)
		err = snd_hda_add_verbs(codec, vt1802_init_verbs);
	else
		err = snd_hda_add_verbs(codec, vt2002P_init_verbs);
	if (err < 0)
		goto error;

	/* automatic parse from the BIOS config */
	err = via_parse_auto_config(codec);
	if (err < 0)
		goto error;

	return 0;

 error:
	via_free(codec);
	return err;
}