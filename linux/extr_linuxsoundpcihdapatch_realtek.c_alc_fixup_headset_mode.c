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
struct hda_fixup {int dummy; } ;
struct hda_codec {struct alc_spec* spec; } ;
struct alc_spec {int parse_flags; int /*<<< orphan*/  current_headset_mode; } ;

/* Variables and functions */
#define  HDA_FIXUP_ACT_INIT 130 
#define  HDA_FIXUP_ACT_PRE_PROBE 129 
#define  HDA_FIXUP_ACT_PROBE 128 
 int HDA_PINCFG_HEADPHONE_MIC ; 
 int HDA_PINCFG_HEADSET_MIC ; 
 int /*<<< orphan*/  alc_probe_headset_mode (struct hda_codec*) ; 
 int /*<<< orphan*/  alc_update_headset_mode (struct hda_codec*) ; 

__attribute__((used)) static void alc_fixup_headset_mode(struct hda_codec *codec,
				const struct hda_fixup *fix, int action)
{
	struct alc_spec *spec = codec->spec;

	switch (action) {
	case HDA_FIXUP_ACT_PRE_PROBE:
		spec->parse_flags |= HDA_PINCFG_HEADSET_MIC | HDA_PINCFG_HEADPHONE_MIC;
		break;
	case HDA_FIXUP_ACT_PROBE:
		alc_probe_headset_mode(codec);
		break;
	case HDA_FIXUP_ACT_INIT:
		spec->current_headset_mode = 0;
		alc_update_headset_mode(codec);
		break;
	}
}