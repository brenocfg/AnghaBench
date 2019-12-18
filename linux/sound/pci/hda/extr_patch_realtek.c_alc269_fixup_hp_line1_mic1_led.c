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
struct hda_fixup {int dummy; } ;
struct hda_codec {struct alc_spec* spec; } ;
struct alc_spec {int cap_mute_led_nid; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  alc269_fixup_hp_mute_led_micx (struct hda_codec*,struct hda_fixup const*,int,int) ; 
 int /*<<< orphan*/  alc_cap_micmute_update ; 
 int /*<<< orphan*/  snd_hda_gen_add_micmute_led (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alc269_fixup_hp_line1_mic1_led(struct hda_codec *codec,
				const struct hda_fixup *fix, int action)
{
	struct alc_spec *spec = codec->spec;

	alc269_fixup_hp_mute_led_micx(codec, fix, action, 0x1a);
	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		spec->cap_mute_led_nid = 0x18;
		snd_hda_gen_add_micmute_led(codec, alc_cap_micmute_update);
	}
}