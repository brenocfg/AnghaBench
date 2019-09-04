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
struct sstfb_par {int /*<<< orphan*/  mmio_vbase; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int mmio_len; int /*<<< orphan*/  mmio_start; int /*<<< orphan*/  smem_start; } ;
struct fb_info {int /*<<< orphan*/  cmap; TYPE_1__ fix; int /*<<< orphan*/  screen_base; int /*<<< orphan*/  dev; struct sstfb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/ * device_attrs ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct fb_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sst_shutdown (struct fb_info*) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static void sstfb_remove(struct pci_dev *pdev)
{
	struct sstfb_par *par;
	struct fb_info *info;

	info = pci_get_drvdata(pdev);
	par = info->par;
	
	device_remove_file(info->dev, &device_attrs[0]);
	sst_shutdown(info);
	iounmap(info->screen_base);
	iounmap(par->mmio_vbase);
	release_mem_region(info->fix.smem_start, 0x400000);
	release_mem_region(info->fix.mmio_start, info->fix.mmio_len);
	fb_dealloc_cmap(&info->cmap);
	unregister_framebuffer(info);
	framebuffer_release(info);
}