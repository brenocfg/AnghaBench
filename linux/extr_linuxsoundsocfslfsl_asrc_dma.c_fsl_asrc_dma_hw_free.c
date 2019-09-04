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
struct snd_pcm_runtime {struct fsl_asrc_pair* private_data; } ;
struct fsl_asrc_pair {int /*<<< orphan*/ ** dma_chan; } ;

/* Variables and functions */
 size_t IN ; 
 size_t OUT ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_set_runtime_buffer (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsl_asrc_dma_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct fsl_asrc_pair *pair = runtime->private_data;

	snd_pcm_set_runtime_buffer(substream, NULL);

	if (pair->dma_chan[IN])
		dma_release_channel(pair->dma_chan[IN]);

	if (pair->dma_chan[OUT])
		dma_release_channel(pair->dma_chan[OUT]);

	pair->dma_chan[IN] = NULL;
	pair->dma_chan[OUT] = NULL;

	return 0;
}