#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int vm_flags; int /*<<< orphan*/ * vm_ops; int /*<<< orphan*/  vm_page_prot; scalar_t__ vm_start; scalar_t__ vm_end; } ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int addr; TYPE_2__ dev; } ;
struct snd_pcm_substream {TYPE_4__* runtime; TYPE_3__ dma_buffer; TYPE_1__* ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  dma_bytes; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  dma_area; } ;
struct TYPE_5__ {int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_HAS_DMA ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 scalar_t__ SNDRV_DMA_TYPE_DEV ; 
 scalar_t__ SNDRV_DMA_TYPE_DEV_IRAM ; 
 int VM_DONTDUMP ; 
 int VM_DONTEXPAND ; 
 int dma_mmap_coherent (int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 int remap_pfn_range (struct vm_area_struct*,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_vm_ops_data_fault ; 

int snd_pcm_lib_default_mmap(struct snd_pcm_substream *substream,
			     struct vm_area_struct *area)
{
	area->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
#ifdef CONFIG_GENERIC_ALLOCATOR
	if (substream->dma_buffer.dev.type == SNDRV_DMA_TYPE_DEV_IRAM) {
		area->vm_page_prot = pgprot_writecombine(area->vm_page_prot);
		return remap_pfn_range(area, area->vm_start,
				substream->dma_buffer.addr >> PAGE_SHIFT,
				area->vm_end - area->vm_start, area->vm_page_prot);
	}
#endif /* CONFIG_GENERIC_ALLOCATOR */
#ifndef CONFIG_X86 /* for avoiding warnings arch/x86/mm/pat.c */
	if (IS_ENABLED(CONFIG_HAS_DMA) && !substream->ops->page &&
	    substream->dma_buffer.dev.type == SNDRV_DMA_TYPE_DEV)
		return dma_mmap_coherent(substream->dma_buffer.dev.dev,
					 area,
					 substream->runtime->dma_area,
					 substream->runtime->dma_addr,
					 substream->runtime->dma_bytes);
#endif /* CONFIG_X86 */
	/* mmap with fault handler */
	area->vm_ops = &snd_pcm_vm_ops_data_fault;
	return 0;
}