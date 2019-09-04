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
struct TYPE_2__ {int /*<<< orphan*/  mixer_nid; } ;
struct alc_spec {TYPE_1__ gen; } ;

/* Variables and functions */
#define  HDA_FIXUP_ACT_INIT 129 
#define  HDA_FIXUP_ACT_PRE_PROBE 128 
 int /*<<< orphan*/  alc_update_coef_idx (struct hda_codec*,int,int,int) ; 
 int /*<<< orphan*/  snd_hda_override_wcaps (struct hda_codec*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alc283_fixup_chromebook(struct hda_codec *codec,
				    const struct hda_fixup *fix, int action)
{
	struct alc_spec *spec = codec->spec;

	switch (action) {
	case HDA_FIXUP_ACT_PRE_PROBE:
		snd_hda_override_wcaps(codec, 0x03, 0);
		/* Disable AA-loopback as it causes white noise */
		spec->gen.mixer_nid = 0;
		break;
	case HDA_FIXUP_ACT_INIT:
		/* MIC2-VREF control */
		/* Set to manual mode */
		alc_update_coef_idx(codec, 0x06, 0x000c, 0);
		/* Enable Line1 input control by verb */
		alc_update_coef_idx(codec, 0x1a, 0, 1 << 4);
		break;
	}
}