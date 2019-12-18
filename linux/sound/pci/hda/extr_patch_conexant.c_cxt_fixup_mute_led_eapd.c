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
struct hda_fixup {int dummy; } ;
struct hda_codec {struct conexant_spec* spec; } ;
struct TYPE_3__ {int /*<<< orphan*/  hook; } ;
struct TYPE_4__ {TYPE_1__ vmaster_mute; } ;
struct conexant_spec {int mute_led_eapd; int dynamic_eapd; TYPE_2__ gen; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  cx_auto_vmaster_hook_mute_led ; 

__attribute__((used)) static void cxt_fixup_mute_led_eapd(struct hda_codec *codec,
				    const struct hda_fixup *fix, int action)
{
	struct conexant_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		spec->mute_led_eapd = 0x1b;
		spec->dynamic_eapd = 1;
		spec->gen.vmaster_mute.hook = cx_auto_vmaster_hook_mute_led;
	}
}