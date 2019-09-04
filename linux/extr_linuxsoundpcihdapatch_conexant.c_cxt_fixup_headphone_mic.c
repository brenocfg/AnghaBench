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
struct hda_codec {int /*<<< orphan*/  core; struct conexant_spec* spec; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* automute_hook ) (struct hda_codec*) ;int /*<<< orphan*/  cap_sync_hook; } ;
struct conexant_spec {TYPE_1__ gen; int /*<<< orphan*/  parse_flags; } ;

/* Variables and functions */
#define  HDA_FIXUP_ACT_INIT 130 
#define  HDA_FIXUP_ACT_PRE_PROBE 129 
#define  HDA_FIXUP_ACT_PROBE 128 
 int /*<<< orphan*/  HDA_PINCFG_HEADPHONE_MIC ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxt_update_headset_mode (struct hda_codec*) ; 
 int /*<<< orphan*/  cxt_update_headset_mode_hook ; 
 int /*<<< orphan*/  snd_hdac_regmap_add_vendor_verb (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void cxt_fixup_headphone_mic(struct hda_codec *codec,
				    const struct hda_fixup *fix, int action)
{
	struct conexant_spec *spec = codec->spec;

	switch (action) {
	case HDA_FIXUP_ACT_PRE_PROBE:
		spec->parse_flags |= HDA_PINCFG_HEADPHONE_MIC;
		snd_hdac_regmap_add_vendor_verb(&codec->core, 0x410);
		break;
	case HDA_FIXUP_ACT_PROBE:
		WARN_ON(spec->gen.cap_sync_hook);
		spec->gen.cap_sync_hook = cxt_update_headset_mode_hook;
		spec->gen.automute_hook = cxt_update_headset_mode;
		break;
	case HDA_FIXUP_ACT_INIT:
		cxt_update_headset_mode(codec);
		break;
	}
}