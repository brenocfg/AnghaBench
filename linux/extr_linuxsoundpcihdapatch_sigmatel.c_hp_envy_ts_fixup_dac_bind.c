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
struct TYPE_2__ {int* preferred_dacs; } ;
struct sigmatel_spec {TYPE_1__ gen; } ;
struct hda_fixup {int dummy; } ;
struct hda_codec {struct sigmatel_spec* spec; } ;
typedef  int hda_nid_t ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 

__attribute__((used)) static void hp_envy_ts_fixup_dac_bind(struct hda_codec *codec,
					    const struct hda_fixup *fix,
					    int action)
{
	struct sigmatel_spec *spec = codec->spec;
	static hda_nid_t preferred_pairs[] = {
		0xd, 0x13,
		0
	};

	if (action != HDA_FIXUP_ACT_PRE_PROBE)
		return;

	spec->gen.preferred_dacs = preferred_pairs;
}