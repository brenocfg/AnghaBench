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
struct pci_dev {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int IRQF_NOBALANCING ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  do_hvm_evtchn_intr ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct pci_dev*) ; 

__attribute__((used)) static int xen_allocate_irq(struct pci_dev *pdev)
{
	return request_irq(pdev->irq, do_hvm_evtchn_intr,
			IRQF_NOBALANCING | IRQF_TRIGGER_RISING,
			"xen-platform-pci", pdev);
}