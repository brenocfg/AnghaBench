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
struct vm_area_struct {int dummy; } ;
struct snd_soc_pcm_runtime {int dummy; } ;
struct snd_soc_component {struct device* dev; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  dma_bytes; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  dma_area; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int dma_mmap_coherent (struct device*,struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int q6asm_dai_mmap(struct snd_pcm_substream *substream,
				struct vm_area_struct *vma)
{

	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_soc_pcm_runtime *soc_prtd = substream->private_data;
	struct snd_soc_component *c = snd_soc_rtdcom_lookup(soc_prtd, DRV_NAME);
	struct device *dev = c->dev;

	return dma_mmap_coherent(dev, vma,
			runtime->dma_area, runtime->dma_addr,
			runtime->dma_bytes);
}