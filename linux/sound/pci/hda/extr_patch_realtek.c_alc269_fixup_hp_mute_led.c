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
struct hda_codec {int /*<<< orphan*/  power_filter; struct alc_spec* spec; } ;
struct dmi_device {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  hook; } ;
struct TYPE_4__ {int vmaster_mute_enum; TYPE_1__ vmaster_mute; } ;
struct alc_spec {int mute_led_polarity; int mute_led_nid; TYPE_2__ gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMI_DEV_TYPE_OEM_STRING ; 
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  alc269_fixup_mic_mute_hook ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,int,int) ; 
 struct dmi_device* dmi_find_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dmi_device const*) ; 
 int /*<<< orphan*/  led_power_filter ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*,int*) ; 

__attribute__((used)) static void alc269_fixup_hp_mute_led(struct hda_codec *codec,
				     const struct hda_fixup *fix, int action)
{
	struct alc_spec *spec = codec->spec;
	const struct dmi_device *dev = NULL;

	if (action != HDA_FIXUP_ACT_PRE_PROBE)
		return;

	while ((dev = dmi_find_device(DMI_DEV_TYPE_OEM_STRING, NULL, dev))) {
		int pol, pin;
		if (sscanf(dev->name, "HP_Mute_LED_%d_%x", &pol, &pin) != 2)
			continue;
		if (pin < 0x0a || pin >= 0x10)
			break;
		spec->mute_led_polarity = pol;
		spec->mute_led_nid = pin - 0x0a + 0x18;
		spec->gen.vmaster_mute.hook = alc269_fixup_mic_mute_hook;
		spec->gen.vmaster_mute_enum = 1;
		codec->power_filter = led_power_filter;
		codec_dbg(codec,
			  "Detected mute LED for %x:%d\n", spec->mute_led_nid,
			   spec->mute_led_polarity);
		break;
	}
}