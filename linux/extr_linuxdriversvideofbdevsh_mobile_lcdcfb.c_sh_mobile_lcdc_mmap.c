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
struct sh_mobile_lcdc_chan {int /*<<< orphan*/  fb_size; int /*<<< orphan*/  dma_handle; int /*<<< orphan*/  fb_mem; TYPE_1__* lcdc; } ;
struct fb_info {struct sh_mobile_lcdc_chan* par; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int dma_mmap_coherent (int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sh_mobile_lcdc_mmap(struct fb_info *info, struct vm_area_struct *vma)
{
	struct sh_mobile_lcdc_chan *ch = info->par;

	return dma_mmap_coherent(ch->lcdc->dev, vma, ch->fb_mem,
				 ch->dma_handle, ch->fb_size);
}