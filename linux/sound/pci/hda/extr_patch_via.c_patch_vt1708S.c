#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mixer_nid; } ;
struct via_spec {TYPE_2__ gen; } ;
struct TYPE_3__ {int vendor_id; } ;
struct hda_codec {TYPE_1__ core; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ VT1708BCE ; 
 scalar_t__ get_codec_type (struct hda_codec*) ; 
 int /*<<< orphan*/  override_mic_boost (struct hda_codec*,int,int /*<<< orphan*/ ,int,int) ; 
 int snd_hda_add_verbs (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_set_name (struct hda_codec*,char*) ; 
 int /*<<< orphan*/  via_free (struct hda_codec*) ; 
 struct via_spec* via_new_spec (struct hda_codec*) ; 
 int via_parse_auto_config (struct hda_codec*) ; 
 int /*<<< orphan*/  vt1708S_init_verbs ; 

__attribute__((used)) static int patch_vt1708S(struct hda_codec *codec)
{
	struct via_spec *spec;
	int err;

	/* create a codec specific record */
	spec = via_new_spec(codec);
	if (spec == NULL)
		return -ENOMEM;

	spec->gen.mixer_nid = 0x16;
	override_mic_boost(codec, 0x1a, 0, 3, 40);
	override_mic_boost(codec, 0x1e, 0, 3, 40);

	/* correct names for VT1708BCE */
	if (get_codec_type(codec) == VT1708BCE)
		snd_hda_codec_set_name(codec, "VT1708BCE");
	/* correct names for VT1705 */
	if (codec->core.vendor_id == 0x11064397)
		snd_hda_codec_set_name(codec, "VT1705");

	err = snd_hda_add_verbs(codec, vt1708S_init_verbs);
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