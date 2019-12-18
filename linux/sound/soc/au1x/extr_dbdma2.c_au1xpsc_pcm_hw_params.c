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
struct snd_pcm_substream {int stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int min_align; scalar_t__ dma_addr; int /*<<< orphan*/  dma_bytes; scalar_t__ dma_area; } ;
struct snd_pcm_hw_params {unsigned long msbits; } ;
struct au1xpsc_audio_dmadata {unsigned long periods; scalar_t__ pos; scalar_t__ curr_period; scalar_t__ q_period; scalar_t__ dma_area; scalar_t__ dma_area_s; int /*<<< orphan*/  period_bytes; struct snd_pcm_substream* substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,unsigned long,unsigned long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MSG (char*) ; 
 int au1x_pcm_dbdma_realloc (struct au1xpsc_audio_dmadata*,int,unsigned long) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_period_bytes (struct snd_pcm_hw_params*) ; 
 unsigned long params_periods (struct snd_pcm_hw_params*) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct au1xpsc_audio_dmadata* to_dmadata (struct snd_pcm_substream*) ; 

__attribute__((used)) static int au1xpsc_pcm_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *params)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct au1xpsc_audio_dmadata *pcd;
	int stype, ret;

	ret = snd_pcm_lib_malloc_pages(substream, params_buffer_bytes(params));
	if (ret < 0)
		goto out;

	stype = substream->stream;
	pcd = to_dmadata(substream);

	DBG("runtime->dma_area = 0x%08lx dma_addr_t = 0x%08lx dma_size = %zu "
	    "runtime->min_align %lu\n",
		(unsigned long)runtime->dma_area,
		(unsigned long)runtime->dma_addr, runtime->dma_bytes,
		runtime->min_align);

	DBG("bits %d  frags %d  frag_bytes %d  is_rx %d\n", params->msbits,
		params_periods(params), params_period_bytes(params), stype);

	ret = au1x_pcm_dbdma_realloc(pcd, stype, params->msbits);
	if (ret) {
		MSG("DDMA channel (re)alloc failed!\n");
		goto out;
	}

	pcd->substream = substream;
	pcd->period_bytes = params_period_bytes(params);
	pcd->periods = params_periods(params);
	pcd->dma_area_s = pcd->dma_area = runtime->dma_addr;
	pcd->q_period = 0;
	pcd->curr_period = 0;
	pcd->pos = 0;

	ret = 0;
out:
	return ret;
}