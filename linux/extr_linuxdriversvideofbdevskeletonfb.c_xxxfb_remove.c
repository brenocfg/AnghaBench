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
struct pci_dev {int dummy; } ;
struct fb_info {int /*<<< orphan*/  cmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 struct fb_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static void xxxfb_remove(struct pci_dev *dev)
{
	struct fb_info *info = pci_get_drvdata(dev);
	/* or platform_get_drvdata(pdev); */

	if (info) {
		unregister_framebuffer(info);
		fb_dealloc_cmap(&info->cmap);
		/* ... */
		framebuffer_release(info);
	}
}