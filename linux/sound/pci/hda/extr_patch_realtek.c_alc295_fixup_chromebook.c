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
struct TYPE_2__ {int /*<<< orphan*/  vendor_id; } ;
struct hda_codec {TYPE_1__ core; struct alc_spec* spec; } ;
struct alc_spec {int ultra_low_power; } ;

/* Variables and functions */
#define  HDA_FIXUP_ACT_INIT 129 
#define  HDA_FIXUP_ACT_PRE_PROBE 128 
 int /*<<< orphan*/  alc_update_coef_idx (struct hda_codec*,int,int,int) ; 

__attribute__((used)) static void alc295_fixup_chromebook(struct hda_codec *codec,
				    const struct hda_fixup *fix, int action)
{
	struct alc_spec *spec = codec->spec;

	switch (action) {
	case HDA_FIXUP_ACT_PRE_PROBE:
		spec->ultra_low_power = true;
		break;
	case HDA_FIXUP_ACT_INIT:
		switch (codec->core.vendor_id) {
		case 0x10ec0295:
			alc_update_coef_idx(codec, 0x4a, 0x8000, 1 << 15); /* Reset HP JD */
			alc_update_coef_idx(codec, 0x4a, 0x8000, 0 << 15);
			break;
		case 0x10ec0236:
			alc_update_coef_idx(codec, 0x1b, 0x8000, 1 << 15); /* Reset HP JD */
			alc_update_coef_idx(codec, 0x1b, 0x8000, 0 << 15);
			break;
		}
		break;
	}
}