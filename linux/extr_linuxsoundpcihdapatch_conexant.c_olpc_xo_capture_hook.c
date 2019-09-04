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
struct snd_pcm_substream {int dummy; } ;
struct hda_pcm_stream {int dummy; } ;
struct hda_codec {struct conexant_spec* spec; } ;
struct conexant_spec {int recording; } ;

/* Variables and functions */
#define  HDA_GEN_PCM_ACT_CLEANUP 129 
#define  HDA_GEN_PCM_ACT_PREPARE 128 
 int /*<<< orphan*/  olpc_xo_update_mic_pins (struct hda_codec*) ; 

__attribute__((used)) static void olpc_xo_capture_hook(struct hda_pcm_stream *hinfo,
				 struct hda_codec *codec,
				 struct snd_pcm_substream *substream,
				 int action)
{
	struct conexant_spec *spec = codec->spec;

	/* toggle spec->recording flag and update mic pins accordingly
	 * for turning on/off LED
	 */
	switch (action) {
	case HDA_GEN_PCM_ACT_PREPARE:
		spec->recording = 1;
		olpc_xo_update_mic_pins(codec);
		break;
	case HDA_GEN_PCM_ACT_CLEANUP:
		spec->recording = 0;
		olpc_xo_update_mic_pins(codec);
		break;
	}
}