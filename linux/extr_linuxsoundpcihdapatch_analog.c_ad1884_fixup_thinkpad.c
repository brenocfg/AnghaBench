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
struct hda_codec {struct ad198x_spec* spec; } ;
struct TYPE_3__ {int /*<<< orphan*/  hook; } ;
struct TYPE_4__ {int keep_eapd_on; scalar_t__ beep_nid; TYPE_1__ vmaster_mute; } ;
struct ad198x_spec {int eapd_nid; TYPE_2__ gen; int /*<<< orphan*/  beep_amp; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_COMPOSE_AMP_VAL (int,int,int,int /*<<< orphan*/ ) ; 
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  HDA_INPUT ; 
 int /*<<< orphan*/  ad_vmaster_eapd_hook ; 

__attribute__((used)) static void ad1884_fixup_thinkpad(struct hda_codec *codec,
				  const struct hda_fixup *fix, int action)
{
	struct ad198x_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		spec->gen.keep_eapd_on = 1;
		spec->gen.vmaster_mute.hook = ad_vmaster_eapd_hook;
		spec->eapd_nid = 0x12;
		/* Analog PC Beeper - allow firmware/ACPI beeps */
		spec->beep_amp = HDA_COMPOSE_AMP_VAL(0x20, 3, 3, HDA_INPUT);
		spec->gen.beep_nid = 0; /* no digital beep */
	}
}