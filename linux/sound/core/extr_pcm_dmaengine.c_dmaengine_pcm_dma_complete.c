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
struct dmaengine_pcm_runtime_data {scalar_t__ pos; } ;

/* Variables and functions */
 scalar_t__ snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 scalar_t__ snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 
 struct dmaengine_pcm_runtime_data* substream_to_prtd (struct snd_pcm_substream*) ; 

__attribute__((used)) static void dmaengine_pcm_dma_complete(void *arg)
{
	struct snd_pcm_substream *substream = arg;
	struct dmaengine_pcm_runtime_data *prtd = substream_to_prtd(substream);

	prtd->pos += snd_pcm_lib_period_bytes(substream);
	if (prtd->pos >= snd_pcm_lib_buffer_bytes(substream))
		prtd->pos = 0;

	snd_pcm_period_elapsed(substream);
}