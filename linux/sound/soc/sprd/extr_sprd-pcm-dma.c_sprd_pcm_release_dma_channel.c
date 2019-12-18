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
struct sprd_pcm_dma_private {struct sprd_pcm_dma_data* data; } ;
struct sprd_pcm_dma_data {int /*<<< orphan*/ * chan; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct sprd_pcm_dma_private* private_data; } ;

/* Variables and functions */
 int SPRD_PCM_CHANNEL_MAX ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sprd_pcm_release_dma_channel(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct sprd_pcm_dma_private *dma_private = runtime->private_data;
	int i;

	for (i = 0; i < SPRD_PCM_CHANNEL_MAX; i++) {
		struct sprd_pcm_dma_data *data = &dma_private->data[i];

		if (data->chan) {
			dma_release_channel(data->chan);
			data->chan = NULL;
		}
	}
}