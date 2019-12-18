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
struct snd_pcm_plugin_format {scalar_t__ channels; scalar_t__ format; int rate; } ;
struct snd_pcm_plugin {int /*<<< orphan*/  action; int /*<<< orphan*/  dst_frames; int /*<<< orphan*/  src_frames; int /*<<< orphan*/  transfer; scalar_t__ extra_data; } ;
struct rate_priv {int pitch; scalar_t__ old_dst_frames; scalar_t__ old_src_frames; scalar_t__ pos; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int ENXIO ; 
 int SHIFT ; 
 scalar_t__ SNDRV_PCM_FORMAT_S16 ; 
 int /*<<< orphan*/  channels ; 
 int /*<<< orphan*/  rate_action ; 
 int /*<<< orphan*/  rate_dst_frames ; 
 int /*<<< orphan*/  rate_init (struct snd_pcm_plugin*) ; 
 int /*<<< orphan*/  rate_src_frames ; 
 int /*<<< orphan*/  rate_transfer ; 
 int /*<<< orphan*/  resample_expand ; 
 int /*<<< orphan*/  resample_shrink ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_pcm_plugin_build (struct snd_pcm_substream*,char*,struct snd_pcm_plugin_format*,struct snd_pcm_plugin_format*,int /*<<< orphan*/ ,struct snd_pcm_plugin**) ; 
 int /*<<< orphan*/  struct_size (struct rate_priv*,int /*<<< orphan*/ ,scalar_t__) ; 

int snd_pcm_plugin_build_rate(struct snd_pcm_substream *plug,
			      struct snd_pcm_plugin_format *src_format,
			      struct snd_pcm_plugin_format *dst_format,
			      struct snd_pcm_plugin **r_plugin)
{
	int err;
	struct rate_priv *data;
	struct snd_pcm_plugin *plugin;

	if (snd_BUG_ON(!r_plugin))
		return -ENXIO;
	*r_plugin = NULL;

	if (snd_BUG_ON(src_format->channels != dst_format->channels))
		return -ENXIO;
	if (snd_BUG_ON(src_format->channels <= 0))
		return -ENXIO;
	if (snd_BUG_ON(src_format->format != SNDRV_PCM_FORMAT_S16))
		return -ENXIO;
	if (snd_BUG_ON(dst_format->format != SNDRV_PCM_FORMAT_S16))
		return -ENXIO;
	if (snd_BUG_ON(src_format->rate == dst_format->rate))
		return -ENXIO;

	err = snd_pcm_plugin_build(plug, "rate conversion",
				   src_format, dst_format,
				   struct_size(data, channels,
					       src_format->channels),
				   &plugin);
	if (err < 0)
		return err;
	data = (struct rate_priv *)plugin->extra_data;
	if (src_format->rate < dst_format->rate) {
		data->pitch = ((src_format->rate << SHIFT) + (dst_format->rate >> 1)) / dst_format->rate;
		data->func = resample_expand;
	} else {
		data->pitch = ((dst_format->rate << SHIFT) + (src_format->rate >> 1)) / src_format->rate;
		data->func = resample_shrink;
	}
	data->pos = 0;
	rate_init(plugin);
	data->old_src_frames = data->old_dst_frames = 0;
	plugin->transfer = rate_transfer;
	plugin->src_frames = rate_src_frames;
	plugin->dst_frames = rate_dst_frames;
	plugin->action = rate_action;
	*r_plugin = plugin;
	return 0;
}