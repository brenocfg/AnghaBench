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
struct TYPE_2__ {int /*<<< orphan*/  hp_automute_hook; } ;
struct alc_spec {TYPE_1__ gen; } ;

/* Variables and functions */
#define  HDA_FIXUP_ACT_INIT 129 
#define  HDA_FIXUP_ACT_PRE_PROBE 128 
 int /*<<< orphan*/  alc283_hp_automute_hook ; 
 int /*<<< orphan*/  alc_update_coef_idx (struct hda_codec*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alc283_fixup_sense_combo_jack(struct hda_codec *codec,
				    const struct hda_fixup *fix, int action)
{
	struct alc_spec *spec = codec->spec;

	switch (action) {
	case HDA_FIXUP_ACT_PRE_PROBE:
		spec->gen.hp_automute_hook = alc283_hp_automute_hook;
		break;
	case HDA_FIXUP_ACT_INIT:
		/* MIC2-VREF control */
		/* Set to manual mode */
		alc_update_coef_idx(codec, 0x06, 0x000c, 0);
		break;
	}
}