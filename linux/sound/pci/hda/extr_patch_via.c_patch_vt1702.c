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
 int AC_AMPCAP_MUTE_SHIFT ; 
 int AC_AMPCAP_NUM_STEPS_SHIFT ; 
 int AC_AMPCAP_OFFSET_SHIFT ; 
 int AC_AMPCAP_STEP_SIZE_SHIFT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HDA_INPUT ; 
 int snd_hda_add_verbs (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_override_amp_caps (struct hda_codec*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  via_free (struct hda_codec*) ; 
 struct via_spec* via_new_spec (struct hda_codec*) ; 
 int via_parse_auto_config (struct hda_codec*) ; 
 int /*<<< orphan*/  vt1702_init_verbs ; 

__attribute__((used)) static int patch_vt1702(struct hda_codec *codec)
{
	struct via_spec *spec;
	int err;

	/* create a codec specific record */
	spec = via_new_spec(codec);
	if (spec == NULL)
		return -ENOMEM;

	spec->gen.mixer_nid = 0x1a;

	/* limit AA path volume to 0 dB */
	snd_hda_override_amp_caps(codec, 0x1A, HDA_INPUT,
				  (0x17 << AC_AMPCAP_OFFSET_SHIFT) |
				  (0x17 << AC_AMPCAP_NUM_STEPS_SHIFT) |
				  (0x5 << AC_AMPCAP_STEP_SIZE_SHIFT) |
				  (1 << AC_AMPCAP_MUTE_SHIFT));

	err = snd_hda_add_verbs(codec, vt1702_init_verbs);
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