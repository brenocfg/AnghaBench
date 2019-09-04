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
struct snd_pcm_plugin_channel {int dummy; } ;
struct snd_pcm_plugin {struct snd_pcm_plugin_channel* buf_channels; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
typedef  int /*<<< orphan*/  snd_pcm_sframes_t ;

/* Variables and functions */

snd_pcm_sframes_t snd_pcm_plugin_client_channels(struct snd_pcm_plugin *plugin,
				       snd_pcm_uframes_t frames,
				       struct snd_pcm_plugin_channel **channels)
{
	*channels = plugin->buf_channels;
	return frames;
}