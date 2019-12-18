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
struct TYPE_2__ {int /*<<< orphan*/  vendor_id; } ;
struct hda_codec {TYPE_1__ core; } ;

/* Variables and functions */
#define  HDA_FIXUP_ACT_INIT 129 
#define  HDA_FIXUP_ACT_PRE_PROBE 128 
 int /*<<< orphan*/  SND_JACK_HEADSET ; 
 int /*<<< orphan*/  alc_headset_btn_callback ; 
 int /*<<< orphan*/  alc_headset_btn_keymap ; 
 int /*<<< orphan*/  alc_update_coef_idx (struct hda_codec*,int,int,int) ; 
 int /*<<< orphan*/  alc_write_coef_idx (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  snd_hda_jack_add_kctl (struct hda_codec*,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_jack_detect_enable_callback (struct hda_codec*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alc_fixup_headset_jack(struct hda_codec *codec,
				    const struct hda_fixup *fix, int action)
{

	switch (action) {
	case HDA_FIXUP_ACT_PRE_PROBE:
		snd_hda_jack_detect_enable_callback(codec, 0x55,
						    alc_headset_btn_callback);
		snd_hda_jack_add_kctl(codec, 0x55, "Headset Jack", false,
				      SND_JACK_HEADSET, alc_headset_btn_keymap);
		break;
	case HDA_FIXUP_ACT_INIT:
		switch (codec->core.vendor_id) {
		case 0x10ec0225:
		case 0x10ec0295:
		case 0x10ec0299:
			alc_write_coef_idx(codec, 0x48, 0xd011);
			alc_update_coef_idx(codec, 0x49, 0x007f, 0x0045);
			alc_update_coef_idx(codec, 0x44, 0x007f << 8, 0x0045 << 8);
			break;
		case 0x10ec0236:
		case 0x10ec0256:
			alc_write_coef_idx(codec, 0x48, 0xd011);
			alc_update_coef_idx(codec, 0x49, 0x007f, 0x0045);
			break;
		}
		break;
	}
}