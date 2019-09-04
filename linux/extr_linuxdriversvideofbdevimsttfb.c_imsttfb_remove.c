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
struct pci_dev {int dummy; } ;
struct imstt_par {int /*<<< orphan*/  dc_regs; int /*<<< orphan*/  cmap_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  smem_start; } ;
struct fb_info {TYPE_1__ fix; int /*<<< orphan*/  screen_base; struct imstt_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct fb_info* pci_get_drvdata (struct pci_dev*) ; 
 int pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static void imsttfb_remove(struct pci_dev *pdev)
{
	struct fb_info *info = pci_get_drvdata(pdev);
	struct imstt_par *par = info->par;
	int size = pci_resource_len(pdev, 0);

	unregister_framebuffer(info);
	iounmap(par->cmap_regs);
	iounmap(par->dc_regs);
	iounmap(info->screen_base);
	release_mem_region(info->fix.smem_start, size);
	framebuffer_release(info);
}