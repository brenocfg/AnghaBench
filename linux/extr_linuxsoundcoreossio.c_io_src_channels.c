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
struct snd_pcm_plugin_channel {int wanted; } ;
struct TYPE_2__ {unsigned int channels; } ;
struct snd_pcm_plugin {scalar_t__ access; TYPE_1__ src_format; } ;
typedef  int snd_pcm_uframes_t ;
typedef  int snd_pcm_sframes_t ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_ACCESS_RW_INTERLEAVED ; 
 int snd_pcm_plugin_client_channels (struct snd_pcm_plugin*,int,struct snd_pcm_plugin_channel**) ; 

__attribute__((used)) static snd_pcm_sframes_t io_src_channels(struct snd_pcm_plugin *plugin,
			     snd_pcm_uframes_t frames,
			     struct snd_pcm_plugin_channel **channels)
{
	int err;
	unsigned int channel;
	struct snd_pcm_plugin_channel *v;
	err = snd_pcm_plugin_client_channels(plugin, frames, &v);
	if (err < 0)
		return err;
	*channels = v;
	if (plugin->access == SNDRV_PCM_ACCESS_RW_INTERLEAVED) {
		for (channel = 0; channel < plugin->src_format.channels; ++channel, ++v)
			v->wanted = 1;
	}
	return frames;
}