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
struct xen_snd_front_pcm_stream_info {int dummy; } ;
struct xen_snd_front_pcm_instance_info {struct xen_snd_front_pcm_stream_info* streams_cap; struct xen_snd_front_pcm_stream_info* streams_pb; } ;
struct snd_pcm_substream {scalar_t__ stream; size_t number; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 struct xen_snd_front_pcm_instance_info* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static struct xen_snd_front_pcm_stream_info *
stream_get(struct snd_pcm_substream *substream)
{
	struct xen_snd_front_pcm_instance_info *pcm_instance =
			snd_pcm_substream_chip(substream);
	struct xen_snd_front_pcm_stream_info *stream;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		stream = &pcm_instance->streams_pb[substream->number];
	else
		stream = &pcm_instance->streams_cap[substream->number];

	return stream;
}