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
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int num_all_adcs; scalar_t__* all_adcs; } ;
struct sigmatel_spec {int active_adcs; TYPE_1__ gen; int /*<<< orphan*/  powerdown_adcs; } ;
struct hda_pcm_stream {scalar_t__ nid; } ;
struct hda_codec {struct sigmatel_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_PWRST_D0 ; 
 int /*<<< orphan*/  AC_PWRST_D3 ; 
 int /*<<< orphan*/  AC_VERB_SET_POWER_STATE ; 
#define  HDA_GEN_PCM_ACT_CLOSE 129 
#define  HDA_GEN_PCM_ACT_OPEN 128 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stac_capture_pcm_hook(struct hda_pcm_stream *hinfo,
				  struct hda_codec *codec,
				  struct snd_pcm_substream *substream,
				  int action)
{
	struct sigmatel_spec *spec = codec->spec;
	int i, idx = 0;

	if (!spec->powerdown_adcs)
		return;

	for (i = 0; i < spec->gen.num_all_adcs; i++) {
		if (spec->gen.all_adcs[i] == hinfo->nid) {
			idx = i;
			break;
		}
	}

	switch (action) {
	case HDA_GEN_PCM_ACT_OPEN:
		msleep(40);
		snd_hda_codec_write(codec, hinfo->nid, 0,
				    AC_VERB_SET_POWER_STATE, AC_PWRST_D0);
		spec->active_adcs |= (1 << idx);
		break;
	case HDA_GEN_PCM_ACT_CLOSE:
		snd_hda_codec_write(codec, hinfo->nid, 0,
				    AC_VERB_SET_POWER_STATE, AC_PWRST_D3);
		spec->active_adcs &= ~(1 << idx);
		break;
	}
}