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
struct TYPE_4__ {int first; int step; } ;
struct snd_pcm_plugin_channel {TYPE_2__ area; } ;
struct TYPE_3__ {unsigned int channels; } ;
struct snd_pcm_plugin {TYPE_1__ src_format; } ;
typedef  scalar_t__ snd_pcm_uframes_t ;
typedef  scalar_t__ snd_pcm_sframes_t ;

/* Variables and functions */
 scalar_t__ ENXIO ; 
 int /*<<< orphan*/  convert (struct snd_pcm_plugin*,struct snd_pcm_plugin_channel const*,struct snd_pcm_plugin_channel*,scalar_t__) ; 
 scalar_t__ snd_BUG_ON (int) ; 

__attribute__((used)) static snd_pcm_sframes_t linear_transfer(struct snd_pcm_plugin *plugin,
			       const struct snd_pcm_plugin_channel *src_channels,
			       struct snd_pcm_plugin_channel *dst_channels,
			       snd_pcm_uframes_t frames)
{
	if (snd_BUG_ON(!plugin || !src_channels || !dst_channels))
		return -ENXIO;
	if (frames == 0)
		return 0;
#ifdef CONFIG_SND_DEBUG
	{
		unsigned int channel;
		for (channel = 0; channel < plugin->src_format.channels; channel++) {
			if (snd_BUG_ON(src_channels[channel].area.first % 8 ||
				       src_channels[channel].area.step % 8))
				return -ENXIO;
			if (snd_BUG_ON(dst_channels[channel].area.first % 8 ||
				       dst_channels[channel].area.step % 8))
				return -ENXIO;
		}
	}
#endif
	convert(plugin, src_channels, dst_channels, frames);
	return frames;
}