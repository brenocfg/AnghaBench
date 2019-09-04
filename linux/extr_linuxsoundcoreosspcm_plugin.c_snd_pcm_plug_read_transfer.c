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
struct snd_pcm_plugin_channel {int dummy; } ;
struct snd_pcm_plugin {int (* client_channels ) (struct snd_pcm_plugin*,int,struct snd_pcm_plugin_channel**) ;int (* transfer ) (struct snd_pcm_plugin*,struct snd_pcm_plugin_channel*,struct snd_pcm_plugin_channel*,int) ;int /*<<< orphan*/  name; struct snd_pcm_plugin* next; } ;
typedef  int snd_pcm_uframes_t ;
typedef  int snd_pcm_sframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  pdprintf (char*,int /*<<< orphan*/ ,int) ; 
 struct snd_pcm_plugin* snd_pcm_plug_first (struct snd_pcm_substream*) ; 
 int snd_pcm_plug_slave_size (struct snd_pcm_substream*,int) ; 
 int stub1 (struct snd_pcm_plugin*,int,struct snd_pcm_plugin_channel**) ; 
 int stub2 (struct snd_pcm_plugin*,struct snd_pcm_plugin_channel*,struct snd_pcm_plugin_channel*,int) ; 

snd_pcm_sframes_t snd_pcm_plug_read_transfer(struct snd_pcm_substream *plug, struct snd_pcm_plugin_channel *dst_channels_final, snd_pcm_uframes_t size)
{
	struct snd_pcm_plugin *plugin, *next;
	struct snd_pcm_plugin_channel *src_channels, *dst_channels;
	snd_pcm_sframes_t frames = size;
	int err;

	frames = snd_pcm_plug_slave_size(plug, frames);
	if (frames < 0)
		return frames;

	src_channels = NULL;
	plugin = snd_pcm_plug_first(plug);
	while (plugin && frames > 0) {
		if ((next = plugin->next) != NULL) {
			if ((err = plugin->client_channels(plugin, frames, &dst_channels)) < 0) {
				return err;
			}
			frames = err;
		} else {
			dst_channels = dst_channels_final;
		}
		pdprintf("read plugin: %s, %li\n", plugin->name, frames);
		if ((frames = plugin->transfer(plugin, src_channels, dst_channels, frames)) < 0)
			return frames;
		plugin = next;
		src_channels = dst_channels;
	}
	return frames;
}