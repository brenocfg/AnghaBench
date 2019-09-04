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
struct fb_info {int /*<<< orphan*/  screen_base; int /*<<< orphan*/  cmap; struct arkfb_info* par; } ;
struct arkfb_info {int /*<<< orphan*/  dac; int /*<<< orphan*/  wc_cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_phys_wc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dac_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 struct fb_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static void ark_pci_remove(struct pci_dev *dev)
{
	struct fb_info *info = pci_get_drvdata(dev);

	if (info) {
		struct arkfb_info *par = info->par;
		arch_phys_wc_del(par->wc_cookie);
		dac_release(par->dac);
		unregister_framebuffer(info);
		fb_dealloc_cmap(&info->cmap);

		pci_iounmap(dev, info->screen_base);
		pci_release_regions(dev);
/*		pci_disable_device(dev); */

		framebuffer_release(info);
	}
}