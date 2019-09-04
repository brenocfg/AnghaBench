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
struct hda_codec {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void request_codec_module(struct hda_codec *codec)
{
#ifdef MODULE
	char modalias[32];
	const char *mod = NULL;

	switch (codec->probe_id) {
	case HDA_CODEC_ID_GENERIC_HDMI:
#if IS_MODULE(CONFIG_SND_HDA_CODEC_HDMI)
		mod = "snd-hda-codec-hdmi";
#endif
		break;
	case HDA_CODEC_ID_GENERIC:
#if IS_MODULE(CONFIG_SND_HDA_GENERIC)
		mod = "snd-hda-codec-generic";
#endif
		break;
	default:
		snd_hdac_codec_modalias(&codec->core, modalias, sizeof(modalias));
		mod = modalias;
		break;
	}

	if (mod)
		request_module(mod);
#endif /* MODULE */
}