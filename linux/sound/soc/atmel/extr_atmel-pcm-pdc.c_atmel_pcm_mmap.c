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
struct vm_area_struct {int /*<<< orphan*/  vm_page_prot; scalar_t__ vm_start; scalar_t__ vm_end; } ;
struct TYPE_2__ {int addr; } ;
struct snd_pcm_substream {TYPE_1__ dma_buffer; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int remap_pfn_range (struct vm_area_struct*,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_pcm_mmap(struct snd_pcm_substream *substream,
	struct vm_area_struct *vma)
{
	return remap_pfn_range(vma, vma->vm_start,
		       substream->dma_buffer.addr >> PAGE_SHIFT,
		       vma->vm_end - vma->vm_start, vma->vm_page_prot);
}