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
struct pci_dev {int dummy; } ;
struct nvidia_par {int /*<<< orphan*/  REGS; int /*<<< orphan*/  wc_cookie; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  modedb; } ;
struct fb_info {TYPE_1__ pixmap; TYPE_2__ monspecs; int /*<<< orphan*/  screen_base; struct nvidia_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVTRACE_ENTER () ; 
 int /*<<< orphan*/  NVTRACE_LEAVE () ; 
 int /*<<< orphan*/  arch_phys_wc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_destroy_modedb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvidia_bl_exit (struct nvidia_par*) ; 
 int /*<<< orphan*/  nvidia_delete_i2c_busses (struct nvidia_par*) ; 
 struct fb_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_framebuffer (struct fb_info*) ; 

__attribute__((used)) static void nvidiafb_remove(struct pci_dev *pd)
{
	struct fb_info *info = pci_get_drvdata(pd);
	struct nvidia_par *par = info->par;

	NVTRACE_ENTER();

	unregister_framebuffer(info);

	nvidia_bl_exit(par);
	arch_phys_wc_del(par->wc_cookie);
	iounmap(info->screen_base);
	fb_destroy_modedb(info->monspecs.modedb);
	nvidia_delete_i2c_busses(par);
	iounmap(par->REGS);
	pci_release_regions(pd);
	kfree(info->pixmap.addr);
	framebuffer_release(info);
	NVTRACE_LEAVE();
}