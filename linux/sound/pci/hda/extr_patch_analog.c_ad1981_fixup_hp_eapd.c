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
struct TYPE_4__ {TYPE_1__ vmaster_mute; } ;
struct ad198x_spec {int eapd_nid; TYPE_2__ gen; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  ad_vmaster_eapd_hook ; 

__attribute__((used)) static void ad1981_fixup_hp_eapd(struct hda_codec *codec,
				 const struct hda_fixup *fix, int action)
{
	struct ad198x_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		spec->gen.vmaster_mute.hook = ad_vmaster_eapd_hook;
		spec->eapd_nid = 0x05;
	}
}