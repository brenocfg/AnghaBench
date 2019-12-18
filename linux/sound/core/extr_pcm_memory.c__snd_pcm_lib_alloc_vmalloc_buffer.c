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
struct snd_pcm_runtime {size_t dma_bytes; scalar_t__ dma_area; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 scalar_t__ PCM_RUNTIME_CHECK (struct snd_pcm_substream*) ; 
 scalar_t__ __vmalloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (scalar_t__) ; 

int _snd_pcm_lib_alloc_vmalloc_buffer(struct snd_pcm_substream *substream,
				      size_t size, gfp_t gfp_flags)
{
	struct snd_pcm_runtime *runtime;

	if (PCM_RUNTIME_CHECK(substream))
		return -EINVAL;
	runtime = substream->runtime;
	if (runtime->dma_area) {
		if (runtime->dma_bytes >= size)
			return 0; /* already large enough */
		vfree(runtime->dma_area);
	}
	runtime->dma_area = __vmalloc(size, gfp_flags, PAGE_KERNEL);
	if (!runtime->dma_area)
		return -ENOMEM;
	runtime->dma_bytes = size;
	return 1;
}