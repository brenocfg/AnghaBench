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
struct xen_pcibk_device {int dummy; } ;
struct pcistub_device {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 struct pcistub_device* pcistub_device_find_locked (int,int,int,int) ; 
 struct pci_dev* pcistub_device_get_pci_dev (struct xen_pcibk_device*,struct pcistub_device*) ; 
 int /*<<< orphan*/  pcistub_devices_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct pci_dev *pcistub_get_pci_dev_by_slot(struct xen_pcibk_device *pdev,
					    int domain, int bus,
					    int slot, int func)
{
	struct pcistub_device *psdev;
	struct pci_dev *found_dev = NULL;
	unsigned long flags;

	spin_lock_irqsave(&pcistub_devices_lock, flags);

	psdev = pcistub_device_find_locked(domain, bus, slot, func);
	if (psdev)
		found_dev = pcistub_device_get_pci_dev(pdev, psdev);

	spin_unlock_irqrestore(&pcistub_devices_lock, flags);
	return found_dev;
}