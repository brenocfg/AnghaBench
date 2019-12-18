#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hda_codec {struct conexant_spec* spec; } ;
struct conexant_spec {int /*<<< orphan*/  dc_enable; } ;

/* Variables and functions */
 int AC_AMP_SET_LEFT ; 
 int AC_AMP_SET_OUTPUT ; 
 int AC_AMP_SET_RIGHT ; 
 int /*<<< orphan*/  AC_VERB_SET_AMP_GAIN_MUTE ; 
 int /*<<< orphan*/  HDA_OUTPUT ; 
 int snd_hda_codec_amp_read (struct hda_codec*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void olpc_xo_update_mic_boost(struct hda_codec *codec)
{
	struct conexant_spec *spec = codec->spec;
	int ch, val;

	for (ch = 0; ch < 2; ch++) {
		val = AC_AMP_SET_OUTPUT |
			(ch ? AC_AMP_SET_RIGHT : AC_AMP_SET_LEFT);
		if (!spec->dc_enable)
			val |= snd_hda_codec_amp_read(codec, 0x17, ch, HDA_OUTPUT, 0);
		snd_hda_codec_write(codec, 0x17, 0,
				    AC_VERB_SET_AMP_GAIN_MUTE, val);
	}
}