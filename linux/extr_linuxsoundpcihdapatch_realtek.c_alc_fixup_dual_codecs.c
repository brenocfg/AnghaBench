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
struct hda_codec {int force_pin_prefix; struct alc_spec* spec; } ;
struct TYPE_2__ {int suppress_vmaster; int suppress_auto_mute; int suppress_auto_mic; scalar_t__ mixer_nid; } ;
struct alc_spec {TYPE_1__ gen; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PRE_PROBE ; 

__attribute__((used)) static void alc_fixup_dual_codecs(struct hda_codec *codec,
				  const struct hda_fixup *fix, int action)
{
	struct alc_spec *spec = codec->spec;

	if (action != HDA_FIXUP_ACT_PRE_PROBE)
		return;
	/* disable vmaster */
	spec->gen.suppress_vmaster = 1;
	/* auto-mute and auto-mic switch don't work with multiple codecs */
	spec->gen.suppress_auto_mute = 1;
	spec->gen.suppress_auto_mic = 1;
	/* disable aamix as well */
	spec->gen.mixer_nid = 0;
	/* add location prefix to avoid conflicts */
	codec->force_pin_prefix = 1;
}