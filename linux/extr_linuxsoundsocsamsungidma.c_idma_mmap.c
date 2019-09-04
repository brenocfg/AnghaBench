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
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; unsigned long vm_pgoff; int /*<<< orphan*/  vm_page_prot; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {unsigned long dma_addr; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int io_remap_pfn_range (struct vm_area_struct*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int idma_mmap(struct snd_pcm_substream *substream,
	struct vm_area_struct *vma)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned long size, offset;
	int ret;

	/* From snd_pcm_lib_mmap_iomem */
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	size = vma->vm_end - vma->vm_start;
	offset = vma->vm_pgoff << PAGE_SHIFT;
	ret = io_remap_pfn_range(vma, vma->vm_start,
			(runtime->dma_addr + offset) >> PAGE_SHIFT,
			size, vma->vm_page_prot);

	return ret;
}