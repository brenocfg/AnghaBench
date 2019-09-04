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
struct pm2fb_par {int /*<<< orphan*/  v_regs; int /*<<< orphan*/  wc_cookie; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct fb_fix_screeninfo {int /*<<< orphan*/  mmio_len; int /*<<< orphan*/  mmio_start; int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; } ;
struct fb_info {TYPE_1__ pixmap; int /*<<< orphan*/  cmap; int /*<<< orphan*/  screen_base; struct pm2fb_par* par; struct fb_fix_screeninfo fix; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_phys_wc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct fb_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static void pm2fb_remove(struct pci_dev *pdev)
{
	struct fb_info *info = pci_get_drvdata(pdev);
	struct fb_fix_screeninfo *fix = &info->fix;
	struct pm2fb_par *par = info->par;

	unregister_framebuffer(info);
	arch_phys_wc_del(par->wc_cookie);
	iounmap(info->screen_base);
	release_mem_region(fix->smem_start, fix->smem_len);
	iounmap(par->v_regs);
	release_mem_region(fix->mmio_start, fix->mmio_len);

	fb_dealloc_cmap(&info->cmap);
	kfree(info->pixmap.addr);
	framebuffer_release(info);
}