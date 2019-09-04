#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct savagefb_par {scalar_t__ pm_state; int /*<<< orphan*/  save; } ;
struct TYPE_10__ {scalar_t__ event; } ;
struct TYPE_7__ {TYPE_4__ power_state; } ;
struct TYPE_8__ {TYPE_1__ power; } ;
struct pci_dev {TYPE_2__ dev; } ;
struct fb_info {TYPE_3__* fbops; struct savagefb_par* par; } ;
typedef  TYPE_4__ pm_message_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* fb_sync ) (struct fb_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 scalar_t__ PM_EVENT_FREEZE ; 
 scalar_t__ PM_EVENT_PRETHAW ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  fb_set_suspend (struct fb_info*,int) ; 
 int /*<<< orphan*/  pci_choose_state (struct pci_dev*,TYPE_4__) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct fb_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  savage_disable_mmio (struct savagefb_par*) ; 
 int /*<<< orphan*/  savage_set_default_par (struct savagefb_par*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  savagefb_blank (int /*<<< orphan*/ ,struct fb_info*) ; 
 int /*<<< orphan*/  stub1 (struct fb_info*) ; 

__attribute__((used)) static int savagefb_suspend(struct pci_dev *dev, pm_message_t mesg)
{
	struct fb_info *info = pci_get_drvdata(dev);
	struct savagefb_par *par = info->par;

	DBG("savagefb_suspend");

	if (mesg.event == PM_EVENT_PRETHAW)
		mesg.event = PM_EVENT_FREEZE;
	par->pm_state = mesg.event;
	dev->dev.power.power_state = mesg;

	/*
	 * For PM_EVENT_FREEZE, do not power down so the console
	 * can remain active.
	 */
	if (mesg.event == PM_EVENT_FREEZE)
		return 0;

	console_lock();
	fb_set_suspend(info, 1);

	if (info->fbops->fb_sync)
		info->fbops->fb_sync(info);

	savagefb_blank(FB_BLANK_POWERDOWN, info);
	savage_set_default_par(par, &par->save);
	savage_disable_mmio(par);
	pci_save_state(dev);
	pci_disable_device(dev);
	pci_set_power_state(dev, pci_choose_state(dev, mesg));
	console_unlock();

	return 0;
}