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
struct hda_fixup {int dummy; } ;
struct hda_codec {struct alc_spec* spec; } ;
struct TYPE_2__ {int hp_mic; } ;
struct alc_spec {TYPE_1__ gen; int /*<<< orphan*/  parse_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_AMP_GAIN_MUTE ; 
 int AC_WCAP_IN_AMP ; 
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  HDA_PINCFG_HEADSET_MIC ; 
 int /*<<< orphan*/  alc_fixup_headset_mode (struct hda_codec*,struct hda_fixup const*,int) ; 
 int get_wcaps (struct hda_codec*,int) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hda_override_wcaps (struct hda_codec*,int,int) ; 

__attribute__((used)) static void alc_fixup_headset_mode_alc662(struct hda_codec *codec,
				const struct hda_fixup *fix, int action)
{
	struct alc_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		spec->parse_flags |= HDA_PINCFG_HEADSET_MIC;
		spec->gen.hp_mic = 1; /* Mic-in is same pin as headphone */

		/* Disable boost for mic-in permanently. (This code is only called
		   from quirks that guarantee that the headphone is at NID 0x1b.) */
		snd_hda_codec_write(codec, 0x1b, 0, AC_VERB_SET_AMP_GAIN_MUTE, 0x7000);
		snd_hda_override_wcaps(codec, 0x1b, get_wcaps(codec, 0x1b) & ~AC_WCAP_IN_AMP);
	} else
		alc_fixup_headset_mode(codec, fix, action);
}