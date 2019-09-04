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
struct snd_pcm_plugin {scalar_t__ (* src_frames ) (struct snd_pcm_plugin*,scalar_t__) ;scalar_t__ (* dst_frames ) (struct snd_pcm_plugin*,scalar_t__) ;struct snd_pcm_plugin* next; struct snd_pcm_plugin* prev; } ;
typedef  scalar_t__ snd_pcm_uframes_t ;
typedef  scalar_t__ snd_pcm_sframes_t ;

/* Variables and functions */
 scalar_t__ ENXIO ; 
 int SNDRV_PCM_STREAM_CAPTURE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  snd_BUG () ; 
 scalar_t__ snd_BUG_ON (int) ; 
 struct snd_pcm_plugin* snd_pcm_plug_first (struct snd_pcm_substream*) ; 
 struct snd_pcm_plugin* snd_pcm_plug_last (struct snd_pcm_substream*) ; 
 int snd_pcm_plug_stream (struct snd_pcm_substream*) ; 
 scalar_t__ stub1 (struct snd_pcm_plugin*,scalar_t__) ; 
 scalar_t__ stub2 (struct snd_pcm_plugin*,scalar_t__) ; 

snd_pcm_sframes_t snd_pcm_plug_client_size(struct snd_pcm_substream *plug, snd_pcm_uframes_t drv_frames)
{
	struct snd_pcm_plugin *plugin, *plugin_prev, *plugin_next;
	int stream;

	if (snd_BUG_ON(!plug))
		return -ENXIO;
	if (drv_frames == 0)
		return 0;
	stream = snd_pcm_plug_stream(plug);
	if (stream == SNDRV_PCM_STREAM_PLAYBACK) {
		plugin = snd_pcm_plug_last(plug);
		while (plugin && drv_frames > 0) {
			plugin_prev = plugin->prev;
			if (plugin->src_frames)
				drv_frames = plugin->src_frames(plugin, drv_frames);
			plugin = plugin_prev;
		}
	} else if (stream == SNDRV_PCM_STREAM_CAPTURE) {
		plugin = snd_pcm_plug_first(plug);
		while (plugin && drv_frames > 0) {
			plugin_next = plugin->next;
			if (plugin->dst_frames)
				drv_frames = plugin->dst_frames(plugin, drv_frames);
			plugin = plugin_next;
		}
	} else
		snd_BUG();
	return drv_frames;
}