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
struct vm_area_struct {int dummy; } ;
struct snd_soc_pcm_runtime {int dummy; } ;
struct snd_soc_component {struct device* dev; } ;
struct snd_compr_stream {struct snd_soc_pcm_runtime* private_data; struct snd_compr_runtime* runtime; } ;
struct snd_compr_runtime {struct q6asm_dai_rtd* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  addr; int /*<<< orphan*/  area; } ;
struct q6asm_dai_rtd {TYPE_1__ dma_buffer; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int dma_mmap_coherent (struct device*,struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int q6asm_dai_compr_mmap(struct snd_compr_stream *stream,
		struct vm_area_struct *vma)
{
	struct snd_compr_runtime *runtime = stream->runtime;
	struct q6asm_dai_rtd *prtd = runtime->private_data;
	struct snd_soc_pcm_runtime *rtd = stream->private_data;
	struct snd_soc_component *c = snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct device *dev = c->dev;

	return dma_mmap_coherent(dev, vma,
			prtd->dma_buffer.area, prtd->dma_buffer.addr,
			prtd->dma_buffer.bytes);
}