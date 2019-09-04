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
struct TYPE_2__ {int no_primary_hp; int no_multi_io; } ;
struct alc_spec {TYPE_1__ gen; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 

__attribute__((used)) static void alc882_fixup_no_primary_hp(struct hda_codec *codec,
				       const struct hda_fixup *fix, int action)
{
	struct alc_spec *spec = codec->spec;
	if (action == HDA_FIXUP_ACT_PRE_PROBE) {
		spec->gen.no_primary_hp = 1;
		spec->gen.no_multi_io = 1;
	}
}