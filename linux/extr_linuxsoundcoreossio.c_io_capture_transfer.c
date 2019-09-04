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
struct TYPE_4__ {void* addr; } ;
struct snd_pcm_plugin_channel {TYPE_2__ area; scalar_t__ enabled; } ;
struct TYPE_3__ {int channels; } ;
struct snd_pcm_plugin {scalar_t__ access; int /*<<< orphan*/  plug; scalar_t__ extra_data; TYPE_1__ dst_format; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
typedef  int /*<<< orphan*/  snd_pcm_sframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 scalar_t__ SNDRV_PCM_ACCESS_RW_INTERLEAVED ; 
 int /*<<< orphan*/  pcm_read (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_readv (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_BUG_ON (int) ; 

__attribute__((used)) static snd_pcm_sframes_t io_capture_transfer(struct snd_pcm_plugin *plugin,
				   const struct snd_pcm_plugin_channel *src_channels,
				   struct snd_pcm_plugin_channel *dst_channels,
				   snd_pcm_uframes_t frames)
{
	if (snd_BUG_ON(!plugin))
		return -ENXIO;
	if (snd_BUG_ON(!dst_channels))
		return -ENXIO;
	if (plugin->access == SNDRV_PCM_ACCESS_RW_INTERLEAVED) {
		return pcm_read(plugin->plug, dst_channels->area.addr, frames);
	} else {
		int channel, channels = plugin->dst_format.channels;
		void **bufs = (void**)plugin->extra_data;
		if (snd_BUG_ON(!bufs))
			return -ENXIO;
		for (channel = 0; channel < channels; channel++) {
			if (dst_channels[channel].enabled)
				bufs[channel] = dst_channels[channel].area.addr;
			else
				bufs[channel] = NULL;
		}
		return pcm_readv(plugin->plug, bufs, frames);
	}
	return 0;
}