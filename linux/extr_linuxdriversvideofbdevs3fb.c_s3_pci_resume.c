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
struct s3fb_info {scalar_t__ ref_count; int /*<<< orphan*/  open_lock; } ;
struct pci_dev {int dummy; } ;
struct fb_info {int /*<<< orphan*/  device; struct s3fb_info* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fb_set_suspend (struct fb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pci_enable_device (struct pci_dev*) ; 
 struct fb_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3fb_set_par (struct fb_info*) ; 

__attribute__((used)) static int s3_pci_resume(struct pci_dev* dev)
{
	struct fb_info *info = pci_get_drvdata(dev);
	struct s3fb_info *par = info->par;
	int err;

	dev_info(info->device, "resume\n");

	console_lock();
	mutex_lock(&(par->open_lock));

	if (par->ref_count == 0) {
		mutex_unlock(&(par->open_lock));
		console_unlock();
		return 0;
	}

	pci_set_power_state(dev, PCI_D0);
	pci_restore_state(dev);
	err = pci_enable_device(dev);
	if (err) {
		mutex_unlock(&(par->open_lock));
		console_unlock();
		dev_err(info->device, "error %d enabling device for resume\n", err);
		return err;
	}
	pci_set_master(dev);

	s3fb_set_par(info);
	fb_set_suspend(info, 0);

	mutex_unlock(&(par->open_lock));
	console_unlock();

	return 0;
}