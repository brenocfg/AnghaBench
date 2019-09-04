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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct gxfb_par {void* gp_regs; void* dc_regs; void* vid_regs; } ;
struct TYPE_2__ {int smem_start; int smem_len; } ;
struct fb_info {TYPE_1__ fix; int /*<<< orphan*/  screen_base; struct gxfb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_GLIU0_MEM_OFFSET ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int gx_frame_buffer_size () ; 
 int /*<<< orphan*/  ioremap_wc (int,int) ; 
 int pci_enable_device (struct pci_dev*) ; 
 void* pci_ioremap_bar (struct pci_dev*,int) ; 
 int pci_request_region (struct pci_dev*,int,char*) ; 
 int pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int vram ; 
 int /*<<< orphan*/  write_dc (struct gxfb_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gxfb_map_video_memory(struct fb_info *info, struct pci_dev *dev)
{
	struct gxfb_par *par = info->par;
	int ret;

	ret = pci_enable_device(dev);
	if (ret < 0)
		return ret;

	ret = pci_request_region(dev, 3, "gxfb (video processor)");
	if (ret < 0)
		return ret;
	par->vid_regs = pci_ioremap_bar(dev, 3);
	if (!par->vid_regs)
		return -ENOMEM;

	ret = pci_request_region(dev, 2, "gxfb (display controller)");
	if (ret < 0)
		return ret;
	par->dc_regs = pci_ioremap_bar(dev, 2);
	if (!par->dc_regs)
		return -ENOMEM;

	ret = pci_request_region(dev, 1, "gxfb (graphics processor)");
	if (ret < 0)
		return ret;
	par->gp_regs = pci_ioremap_bar(dev, 1);

	if (!par->gp_regs)
		return -ENOMEM;

	ret = pci_request_region(dev, 0, "gxfb (framebuffer)");
	if (ret < 0)
		return ret;

	info->fix.smem_start = pci_resource_start(dev, 0);
	info->fix.smem_len = vram ? vram : gx_frame_buffer_size();
	info->screen_base = ioremap_wc(info->fix.smem_start,
				       info->fix.smem_len);
	if (!info->screen_base)
		return -ENOMEM;

	/* Set the 16MiB aligned base address of the graphics memory region
	 * in the display controller */

	write_dc(par, DC_GLIU0_MEM_OFFSET, info->fix.smem_start & 0xFF000000);

	dev_info(&dev->dev, "%d KiB of video memory at 0x%lx\n",
		 info->fix.smem_len / 1024, info->fix.smem_start);

	return 0;
}