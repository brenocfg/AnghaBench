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
typedef  long long u64 ;
struct snd_pcm_substream {scalar_t__ stream; TYPE_1__* runtime; } ;
struct TYPE_4__ {long long (* get_delay ) (struct hda_pcm_stream*,int /*<<< orphan*/ ,struct snd_pcm_substream*) ;} ;
struct hda_pcm_stream {TYPE_2__ ops; } ;
struct azx_pcm {int /*<<< orphan*/  codec; } ;
struct TYPE_3__ {int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 long long div_u64 (long long,int /*<<< orphan*/ ) ; 
 struct azx_pcm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 long long stub1 (struct hda_pcm_stream*,int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 
 struct hda_pcm_stream* to_hda_pcm_stream (struct snd_pcm_substream*) ; 

__attribute__((used)) static u64 azx_adjust_codec_delay(struct snd_pcm_substream *substream,
				u64 nsec)
{
	struct azx_pcm *apcm = snd_pcm_substream_chip(substream);
	struct hda_pcm_stream *hinfo = to_hda_pcm_stream(substream);
	u64 codec_frames, codec_nsecs;

	if (!hinfo->ops.get_delay)
		return nsec;

	codec_frames = hinfo->ops.get_delay(hinfo, apcm->codec, substream);
	codec_nsecs = div_u64(codec_frames * 1000000000LL,
			      substream->runtime->rate);

	if (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		return nsec + codec_nsecs;

	return (nsec > codec_nsecs) ? nsec - codec_nsecs : 0;
}