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
struct snd_pcm_runtime {scalar_t__ dma_area; scalar_t__ control; scalar_t__ status; } ;
struct snd_pcm_file {struct snd_pcm_substream* substream; } ;
struct file {struct snd_pcm_file* private_data; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
#define  SNDRV_PCM_MMAP_OFFSET_CONTROL 129 
#define  SNDRV_PCM_MMAP_OFFSET_STATUS 128 

__attribute__((used)) static unsigned long snd_pcm_get_unmapped_area(struct file *file,
					       unsigned long addr,
					       unsigned long len,
					       unsigned long pgoff,
					       unsigned long flags)
{
	struct snd_pcm_file *pcm_file = file->private_data;
	struct snd_pcm_substream *substream = pcm_file->substream;
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned long offset = pgoff << PAGE_SHIFT;

	switch (offset) {
	case SNDRV_PCM_MMAP_OFFSET_STATUS:
		return (unsigned long)runtime->status;
	case SNDRV_PCM_MMAP_OFFSET_CONTROL:
		return (unsigned long)runtime->control;
	default:
		return (unsigned long)runtime->dma_area + offset;
	}
}