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
struct via_spec {TYPE_1__ gen; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  override_mic_boost (struct hda_codec*,int,int /*<<< orphan*/ ,int,int) ; 
 int snd_hda_add_verbs (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_gen_add_kctl (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  via_free (struct hda_codec*) ; 
 struct via_spec* via_new_spec (struct hda_codec*) ; 
 int via_parse_auto_config (struct hda_codec*) ; 
 int /*<<< orphan*/  vt1716S_init_verbs ; 
 int /*<<< orphan*/  vt1716S_mono_out_mixer ; 
 int /*<<< orphan*/  vt1716s_dmic_mixer_sw ; 
 int /*<<< orphan*/  vt1716s_dmic_mixer_vol ; 

__attribute__((used)) static int patch_vt1716S(struct hda_codec *codec)
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

	err = snd_hda_add_verbs(codec, vt1716S_init_verbs);
	if (err < 0)
		goto error;

	/* automatic parse from the BIOS config */
	err = via_parse_auto_config(codec);
	if (err < 0)
		goto error;

	if (!snd_hda_gen_add_kctl(&spec->gen, NULL, &vt1716s_dmic_mixer_vol) ||
	    !snd_hda_gen_add_kctl(&spec->gen, NULL, &vt1716s_dmic_mixer_sw) ||
	    !snd_hda_gen_add_kctl(&spec->gen, NULL, &vt1716S_mono_out_mixer)) {
		err = -ENOMEM;
		goto error;
	}

	return 0;

 error:
	via_free(codec);
	return err;
}