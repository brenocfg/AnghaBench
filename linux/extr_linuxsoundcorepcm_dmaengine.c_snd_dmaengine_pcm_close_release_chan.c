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
struct dmaengine_pcm_runtime_data {int /*<<< orphan*/  dma_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_synchronize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dmaengine_pcm_runtime_data*) ; 
 struct dmaengine_pcm_runtime_data* substream_to_prtd (struct snd_pcm_substream*) ; 

int snd_dmaengine_pcm_close_release_chan(struct snd_pcm_substream *substream)
{
	struct dmaengine_pcm_runtime_data *prtd = substream_to_prtd(substream);

	dmaengine_synchronize(prtd->dma_chan);
	dma_release_channel(prtd->dma_chan);
	kfree(prtd);

	return 0;
}