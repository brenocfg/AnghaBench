#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hda_pintbl {int member_0; int member_1; } ;
struct hda_fixup {int dummy; } ;
struct hda_codec {struct alc_spec* spec; } ;
struct alc_spec {int /*<<< orphan*/  init_amp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALC_INIT_NONE ; 
#define  HDA_FIXUP_ACT_PRE_PROBE 128 
 int /*<<< orphan*/  snd_hda_apply_pincfgs (struct hda_codec*,struct hda_pintbl const*) ; 

__attribute__((used)) static void alc260_fixup_kn1(struct hda_codec *codec,
			     const struct hda_fixup *fix, int action)
{
	struct alc_spec *spec = codec->spec;
	static const struct hda_pintbl pincfgs[] = {
		{ 0x0f, 0x02214000 }, /* HP/speaker */
		{ 0x12, 0x90a60160 }, /* int mic */
		{ 0x13, 0x02a19000 }, /* ext mic */
		{ 0x18, 0x01446000 }, /* SPDIF out */
		/* disable bogus I/O pins */
		{ 0x10, 0x411111f0 },
		{ 0x11, 0x411111f0 },
		{ 0x14, 0x411111f0 },
		{ 0x15, 0x411111f0 },
		{ 0x16, 0x411111f0 },
		{ 0x17, 0x411111f0 },
		{ 0x19, 0x411111f0 },
		{ }
	};

	switch (action) {
	case HDA_FIXUP_ACT_PRE_PROBE:
		snd_hda_apply_pincfgs(codec, pincfgs);
		spec->init_amp = ALC_INIT_NONE;
		break;
	}
}