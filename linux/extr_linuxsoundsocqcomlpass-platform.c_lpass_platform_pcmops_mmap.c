#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int dummy; } ;
struct snd_pcm_substream {TYPE_2__* pcm; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  dma_bytes; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  dma_area; } ;
struct TYPE_4__ {TYPE_1__* card; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int dma_mmap_coherent (int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpass_platform_pcmops_mmap(struct snd_pcm_substream *substream,
		struct vm_area_struct *vma)
{
	struct snd_pcm_runtime *runtime = substream->runtime;

	return dma_mmap_coherent(substream->pcm->card->dev, vma,
			runtime->dma_area, runtime->dma_addr,
			runtime->dma_bytes);
}