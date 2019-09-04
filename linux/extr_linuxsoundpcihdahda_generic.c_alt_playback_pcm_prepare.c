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
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_GEN_PCM_ACT_PREPARE ; 
 int /*<<< orphan*/  call_pcm_playback_hook (struct hda_pcm_stream*,struct hda_codec*,struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_setup_stream (struct hda_codec*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int alt_playback_pcm_prepare(struct hda_pcm_stream *hinfo,
				    struct hda_codec *codec,
				    unsigned int stream_tag,
				    unsigned int format,
				    struct snd_pcm_substream *substream)
{
	snd_hda_codec_setup_stream(codec, hinfo->nid, stream_tag, 0, format);
	call_pcm_playback_hook(hinfo, codec, substream,
			       HDA_GEN_PCM_ACT_PREPARE);
	return 0;
}