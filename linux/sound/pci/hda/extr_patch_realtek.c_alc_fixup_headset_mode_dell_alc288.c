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
struct TYPE_2__ {int /*<<< orphan*/  hp_automute_hook; } ;
struct alc_spec {int gpio_mask; int gpio_dir; TYPE_1__ gen; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PROBE ; 
 int /*<<< orphan*/  alc288_update_headset_jack_cb ; 
 int /*<<< orphan*/  alc_fixup_headset_mode (struct hda_codec*,struct hda_fixup const*,int) ; 

__attribute__((used)) static void alc_fixup_headset_mode_dell_alc288(struct hda_codec *codec,
				const struct hda_fixup *fix, int action)
{
	alc_fixup_headset_mode(codec, fix, action);
	if (action == HDA_FIXUP_ACT_PROBE) {
		struct alc_spec *spec = codec->spec;
		/* toggled via hp_automute_hook */
		spec->gpio_mask |= 0x40;
		spec->gpio_dir |= 0x40;
		spec->gen.hp_automute_hook = alc288_update_headset_jack_cb;
	}
}