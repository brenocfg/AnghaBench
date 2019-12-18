#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int /*<<< orphan*/  put; } ;
struct hda_fixup {int dummy; } ;
struct hda_codec {struct cs_spec* spec; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dig_out_pins; } ;
struct TYPE_4__ {TYPE_1__ autocfg; } ;
struct cs_spec {int /*<<< orphan*/  spdif_sw_put; TYPE_2__ gen; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_BUILD ; 
 int /*<<< orphan*/  cs4208_spdif_sw_put ; 
 struct snd_kcontrol* snd_hda_find_mixer_ctl (struct hda_codec*,char*) ; 

__attribute__((used)) static void cs4208_fixup_spdif_switch(struct hda_codec *codec,
				      const struct hda_fixup *fix, int action)
{
	if (action == HDA_FIXUP_ACT_BUILD) {
		struct cs_spec *spec = codec->spec;
		struct snd_kcontrol *kctl;

		if (!spec->gen.autocfg.dig_out_pins[0])
			return;
		kctl = snd_hda_find_mixer_ctl(codec, "IEC958 Playback Switch");
		if (!kctl)
			return;
		spec->spdif_sw_put = kctl->put;
		kctl->put = cs4208_spdif_sw_put;
	}
}