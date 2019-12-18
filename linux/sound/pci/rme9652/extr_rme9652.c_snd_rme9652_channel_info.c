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
struct snd_rme9652 {int* channel_map; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_channel_info {scalar_t__ channel; int offset; int step; scalar_t__ first; } ;

/* Variables and functions */
 int EINVAL ; 
 int RME9652_CHANNEL_BUFFER_BYTES ; 
 scalar_t__ RME9652_NCHANNELS ; 
 size_t array_index_nospec (scalar_t__,scalar_t__) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 struct snd_rme9652* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_rme9652_channel_info(struct snd_pcm_substream *substream,
				    struct snd_pcm_channel_info *info)
{
	struct snd_rme9652 *rme9652 = snd_pcm_substream_chip(substream);
	int chn;

	if (snd_BUG_ON(info->channel >= RME9652_NCHANNELS))
		return -EINVAL;

	chn = rme9652->channel_map[array_index_nospec(info->channel,
						      RME9652_NCHANNELS)];
	if (chn < 0)
		return -EINVAL;

	info->offset = chn * RME9652_CHANNEL_BUFFER_BYTES;
	info->first = 0;
	info->step = 32;
	return 0;
}