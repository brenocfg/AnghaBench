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
struct dmaengine_pcm_runtime_data {struct dma_chan* dma_chan; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 struct dmaengine_pcm_runtime_data* substream_to_prtd (struct snd_pcm_substream*) ; 

struct dma_chan *snd_dmaengine_pcm_get_chan(struct snd_pcm_substream *substream)
{
	struct dmaengine_pcm_runtime_data *prtd = substream_to_prtd(substream);

	return prtd->dma_chan;
}