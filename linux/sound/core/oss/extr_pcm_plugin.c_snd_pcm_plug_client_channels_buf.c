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
struct snd_pcm_plugin_format {int channels; int /*<<< orphan*/  format; } ;
struct TYPE_2__ {char* addr; int first; int step; } ;
struct snd_pcm_plugin_channel {int frames; int enabled; int wanted; TYPE_1__ area; } ;
struct snd_pcm_plugin {scalar_t__ access; struct snd_pcm_plugin_channel* buf_channels; struct snd_pcm_plugin_format dst_format; struct snd_pcm_plugin_format src_format; } ;
typedef  int snd_pcm_uframes_t ;
typedef  int snd_pcm_sframes_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ SNDRV_PCM_ACCESS_RW_INTERLEAVED ; 
 int SNDRV_PCM_STREAM_CAPTURE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_pcm_format_physical_width (int /*<<< orphan*/ ) ; 
 struct snd_pcm_plugin* snd_pcm_plug_first (struct snd_pcm_substream*) ; 
 struct snd_pcm_plugin* snd_pcm_plug_last (struct snd_pcm_substream*) ; 
 int snd_pcm_plug_stream (struct snd_pcm_substream*) ; 

snd_pcm_sframes_t snd_pcm_plug_client_channels_buf(struct snd_pcm_substream *plug,
					 char *buf,
					 snd_pcm_uframes_t count,
					 struct snd_pcm_plugin_channel **channels)
{
	struct snd_pcm_plugin *plugin;
	struct snd_pcm_plugin_channel *v;
	struct snd_pcm_plugin_format *format;
	int width, nchannels, channel;
	int stream = snd_pcm_plug_stream(plug);

	if (snd_BUG_ON(!buf))
		return -ENXIO;
	if (stream == SNDRV_PCM_STREAM_PLAYBACK) {
		plugin = snd_pcm_plug_first(plug);
		format = &plugin->src_format;
	} else {
		plugin = snd_pcm_plug_last(plug);
		format = &plugin->dst_format;
	}
	v = plugin->buf_channels;
	*channels = v;
	if ((width = snd_pcm_format_physical_width(format->format)) < 0)
		return width;
	nchannels = format->channels;
	if (snd_BUG_ON(plugin->access != SNDRV_PCM_ACCESS_RW_INTERLEAVED &&
		       format->channels > 1))
		return -ENXIO;
	for (channel = 0; channel < nchannels; channel++, v++) {
		v->frames = count;
		v->enabled = 1;
		v->wanted = (stream == SNDRV_PCM_STREAM_CAPTURE);
		v->area.addr = buf;
		v->area.first = channel * width;
		v->area.step = nchannels * width;
	}
	return count;
}