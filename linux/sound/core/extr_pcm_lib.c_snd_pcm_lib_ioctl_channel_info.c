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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int info; int access; int channels; size_t dma_bytes; int /*<<< orphan*/  format; } ;
struct snd_pcm_channel_info {int offset; int first; int channel; int step; } ;

/* Variables and functions */
#define  SNDRV_PCM_ACCESS_MMAP_INTERLEAVED 131 
#define  SNDRV_PCM_ACCESS_MMAP_NONINTERLEAVED 130 
#define  SNDRV_PCM_ACCESS_RW_INTERLEAVED 129 
#define  SNDRV_PCM_ACCESS_RW_NONINTERLEAVED 128 
 int SNDRV_PCM_INFO_MMAP ; 
 int /*<<< orphan*/  snd_BUG () ; 
 int snd_pcm_format_physical_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_pcm_lib_ioctl_channel_info(struct snd_pcm_substream *substream,
					  void *arg)
{
	struct snd_pcm_channel_info *info = arg;
	struct snd_pcm_runtime *runtime = substream->runtime;
	int width;
	if (!(runtime->info & SNDRV_PCM_INFO_MMAP)) {
		info->offset = -1;
		return 0;
	}
	width = snd_pcm_format_physical_width(runtime->format);
	if (width < 0)
		return width;
	info->offset = 0;
	switch (runtime->access) {
	case SNDRV_PCM_ACCESS_MMAP_INTERLEAVED:
	case SNDRV_PCM_ACCESS_RW_INTERLEAVED:
		info->first = info->channel * width;
		info->step = runtime->channels * width;
		break;
	case SNDRV_PCM_ACCESS_MMAP_NONINTERLEAVED:
	case SNDRV_PCM_ACCESS_RW_NONINTERLEAVED:
	{
		size_t size = runtime->dma_bytes / runtime->channels;
		info->first = info->channel * size * 8;
		info->step = width;
		break;
	}
	default:
		snd_BUG();
		break;
	}
	return 0;
}