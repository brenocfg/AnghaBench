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
struct hda_gen_spec {int /*<<< orphan*/  multiout; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_GEN_PCM_ACT_CLEANUP ; 
 int /*<<< orphan*/  call_pcm_playback_hook (struct hda_pcm_stream*,struct hda_codec*,struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int snd_hda_multi_out_analog_cleanup (struct hda_codec*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int playback_pcm_cleanup(struct hda_pcm_stream *hinfo,
				struct hda_codec *codec,
				struct snd_pcm_substream *substream)
{
	struct hda_gen_spec *spec = codec->spec;
	int err;

	err = snd_hda_multi_out_analog_cleanup(codec, &spec->multiout);
	if (!err)
		call_pcm_playback_hook(hinfo, codec, substream,
				       HDA_GEN_PCM_ACT_CLEANUP);
	return err;
}