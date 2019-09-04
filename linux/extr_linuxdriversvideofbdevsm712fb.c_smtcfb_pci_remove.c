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
struct smtcfb_info {int /*<<< orphan*/  fb; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  framebuffer_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct smtcfb_info* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smtc_unmap_mmio (struct smtcfb_info*) ; 
 int /*<<< orphan*/  smtc_unmap_smem (struct smtcfb_info*) ; 
 int /*<<< orphan*/  unregister_framebuffer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smtcfb_pci_remove(struct pci_dev *pdev)
{
	struct smtcfb_info *sfb;

	sfb = pci_get_drvdata(pdev);
	smtc_unmap_smem(sfb);
	smtc_unmap_mmio(sfb);
	unregister_framebuffer(sfb->fb);
	framebuffer_release(sfb->fb);
	pci_release_region(pdev, 0);
	pci_disable_device(pdev);
}