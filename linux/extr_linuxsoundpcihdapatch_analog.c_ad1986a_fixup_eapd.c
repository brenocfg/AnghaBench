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
struct hda_codec {scalar_t__ inv_eapd; struct ad198x_spec* spec; } ;
struct TYPE_2__ {int keep_eapd_on; } ;
struct ad198x_spec {int eapd_nid; TYPE_1__ gen; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 

__attribute__((used)) static void ad1986a_fixup_eapd(struct hda_codec *codec,
			       const struct hda_fixup *fix, int action)
{
	struct ad198x_spec *spec = codec->spec;

	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		codec->inv_eapd = 0;
		spec->gen.keep_eapd_on = 1;
		spec->eapd_nid = 0x1b;
	}
}