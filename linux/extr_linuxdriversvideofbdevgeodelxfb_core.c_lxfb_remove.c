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
struct lxfb_par {int /*<<< orphan*/  vp_regs; int /*<<< orphan*/  dc_regs; int /*<<< orphan*/  gp_regs; } ;
struct fb_info {int /*<<< orphan*/  cmap; int /*<<< orphan*/  screen_base; struct lxfb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct fb_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static void lxfb_remove(struct pci_dev *pdev)
{
	struct fb_info *info = pci_get_drvdata(pdev);
	struct lxfb_par *par = info->par;

	unregister_framebuffer(info);

	iounmap(info->screen_base);
	pci_release_region(pdev, 0);

	iounmap(par->gp_regs);
	pci_release_region(pdev, 1);

	iounmap(par->dc_regs);
	pci_release_region(pdev, 2);

	iounmap(par->vp_regs);
	pci_release_region(pdev, 3);

	fb_dealloc_cmap(&info->cmap);
	framebuffer_release(info);
}