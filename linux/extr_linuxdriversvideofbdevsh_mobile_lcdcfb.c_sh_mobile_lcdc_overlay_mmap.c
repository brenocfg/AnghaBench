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
struct sh_mobile_lcdc_overlay {int /*<<< orphan*/  fb_size; int /*<<< orphan*/  dma_handle; int /*<<< orphan*/  fb_mem; TYPE_2__* channel; } ;
struct fb_info {struct sh_mobile_lcdc_overlay* par; } ;
struct TYPE_4__ {TYPE_1__* lcdc; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int dma_mmap_coherent (int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sh_mobile_lcdc_overlay_mmap(struct fb_info *info, struct vm_area_struct *vma)
{
	struct sh_mobile_lcdc_overlay *ovl = info->par;

	return dma_mmap_coherent(ovl->channel->lcdc->dev, vma, ovl->fb_mem,
				 ovl->dma_handle, ovl->fb_size);
}