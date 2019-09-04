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
struct hda_pcm_stream {int /*<<< orphan*/  nid; } ;
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {scalar_t__ dsp_state; } ;

/* Variables and functions */
 scalar_t__ DSP_DOWNLOADING ; 
 int /*<<< orphan*/  snd_hda_codec_cleanup_stream (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ca0132_capture_pcm_cleanup(struct hda_pcm_stream *hinfo,
			struct hda_codec *codec,
			struct snd_pcm_substream *substream)
{
	struct ca0132_spec *spec = codec->spec;

	if (spec->dsp_state == DSP_DOWNLOADING)
		return 0;

	snd_hda_codec_cleanup_stream(codec, hinfo->nid);
	return 0;
}