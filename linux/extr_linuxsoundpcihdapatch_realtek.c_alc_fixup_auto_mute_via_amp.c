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
struct TYPE_2__ {int auto_mute_via_amp; } ;
struct alc_spec {TYPE_1__ gen; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 

__attribute__((used)) static void alc_fixup_auto_mute_via_amp(struct hda_codec *codec,
					const struct hda_fixup *fix, int action)
{
	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		struct alc_spec *spec = codec->spec;
		spec->gen.auto_mute_via_amp = 1;
	}
}