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
struct hda_codec {struct alc_spec* spec; } ;
struct TYPE_3__ {int* speaker_pins; } ;
struct TYPE_4__ {int beep_nid; TYPE_1__ autocfg; int /*<<< orphan*/  no_analog; } ;
struct alc_spec {TYPE_2__ gen; int /*<<< orphan*/  shutup; } ;

/* Variables and functions */
 int AC_AMPCAP_MUTE_SHIFT ; 
 int AC_AMPCAP_NUM_STEPS_SHIFT ; 
 int AC_AMPCAP_OFFSET_SHIFT ; 
 int AC_AMPCAP_STEP_SIZE_SHIFT ; 
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  HDA_FIXUP_ACT_PROBE ; 
 int /*<<< orphan*/  HDA_INPUT ; 
 int /*<<< orphan*/  alc268_beep_init_verbs ; 
 int /*<<< orphan*/ * alc268_beep_mixer ; 
 int /*<<< orphan*/  alc268_fixup_models ; 
 int /*<<< orphan*/  alc268_fixup_tbl ; 
 int /*<<< orphan*/  alc268_fixups ; 
 int alc268_parse_auto_config (struct hda_codec*) ; 
 int alc_alloc_spec (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alc_eapd_shutup ; 
 int /*<<< orphan*/  alc_free (struct hda_codec*) ; 
 int /*<<< orphan*/  alc_pre_init (struct hda_codec*) ; 
 scalar_t__ has_cdefine_beep (struct hda_codec*) ; 
 int /*<<< orphan*/  query_amp_caps (struct hda_codec*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_add_verbs (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_apply_fixup (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_gen_add_kctl (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hda_override_amp_caps (struct hda_codec*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hda_pick_fixup (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int patch_alc268(struct hda_codec *codec)
{
	struct alc_spec *spec;
	int i, err;

	/* ALC268 has no aa-loopback mixer */
	err = alc_alloc_spec(codec, 0);
	if (err < 0)
		return err;

	spec = codec->spec;
	if (has_cdefine_beep(codec))
		spec->gen.beep_nid = 0x01;

	spec->shutup = alc_eapd_shutup;

	alc_pre_init(codec);

	snd_hda_pick_fixup(codec, alc268_fixup_models, alc268_fixup_tbl, alc268_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	/* automatic parse from the BIOS config */
	err = alc268_parse_auto_config(codec);
	if (err < 0)
		goto error;

	if (err > 0 && !spec->gen.no_analog &&
	    spec->gen.autocfg.speaker_pins[0] != 0x1d) {
		for (i = 0; i < ARRAY_SIZE(alc268_beep_mixer); i++) {
			if (!snd_hda_gen_add_kctl(&spec->gen, NULL,
						  &alc268_beep_mixer[i])) {
				err = -ENOMEM;
				goto error;
			}
		}
		snd_hda_add_verbs(codec, alc268_beep_init_verbs);
		if (!query_amp_caps(codec, 0x1d, HDA_INPUT))
			/* override the amp caps for beep generator */
			snd_hda_override_amp_caps(codec, 0x1d, HDA_INPUT,
					  (0x0c << AC_AMPCAP_OFFSET_SHIFT) |
					  (0x0c << AC_AMPCAP_NUM_STEPS_SHIFT) |
					  (0x07 << AC_AMPCAP_STEP_SIZE_SHIFT) |
					  (0 << AC_AMPCAP_MUTE_SHIFT));
	}

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	return 0;

 error:
	alc_free(codec);
	return err;
}