#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  addr; scalar_t__ area; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; TYPE_1__ dma_buffer; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  dma_area; struct i2s_stream_instance* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct i2s_stream_instance {int num_pages; int /*<<< orphan*/  dma_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  config_acp3x_dma (struct i2s_stream_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acp3x_dma_hw_params(struct snd_pcm_substream *substream,
			       struct snd_pcm_hw_params *params)
{
	int status;
	u64 size;
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct i2s_stream_instance *rtd = runtime->private_data;

	if (!rtd)
		return -EINVAL;

	size = params_buffer_bytes(params);
	status = snd_pcm_lib_malloc_pages(substream, size);
	if (status < 0)
		return status;

	memset(substream->runtime->dma_area, 0, params_buffer_bytes(params));
	if (substream->dma_buffer.area) {
		rtd->dma_addr = substream->dma_buffer.addr;
		rtd->num_pages = (PAGE_ALIGN(size) >> PAGE_SHIFT);
		config_acp3x_dma(rtd, substream->stream);
		status = 0;
	} else {
		status = -ENOMEM;
	}
	return status;
}