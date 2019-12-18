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
struct snd_pcm_channel_info {unsigned int channel; int offset; int step; scalar_t__ first; } ;
struct hdsp {unsigned int max_channels; int* channel_map; } ;

/* Variables and functions */
 int EINVAL ; 
 int HDSP_CHANNEL_BUFFER_BYTES ; 
 unsigned int array_index_nospec (unsigned int,unsigned int) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 struct hdsp* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_hdsp_channel_info(struct snd_pcm_substream *substream,
				    struct snd_pcm_channel_info *info)
{
	struct hdsp *hdsp = snd_pcm_substream_chip(substream);
	unsigned int channel = info->channel;

	if (snd_BUG_ON(channel >= hdsp->max_channels))
		return -EINVAL;
	channel = array_index_nospec(channel, hdsp->max_channels);

	if (hdsp->channel_map[channel] < 0)
		return -EINVAL;

	info->offset = hdsp->channel_map[channel] * HDSP_CHANNEL_BUFFER_BYTES;
	info->first = 0;
	info->step = 32;
	return 0;
}