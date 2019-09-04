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
struct pci_device_id {scalar_t__ vendor; scalar_t__ device; } ;
struct pci_dev {scalar_t__ vendor; scalar_t__ device; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct pci_device_id const*) ; 
 int ENODEV ; 
 struct pci_device_id const* blacklist ; 

__attribute__((used)) static int serial_pci_is_blacklisted(struct pci_dev *dev)
{
	const struct pci_device_id *bldev;

	/*
	 * Do not access blacklisted devices that are known not to
	 * feature serial ports or are handled by other modules.
	 */
	for (bldev = blacklist;
	     bldev < blacklist + ARRAY_SIZE(blacklist);
	     bldev++) {
		if (dev->vendor == bldev->vendor &&
		    dev->device == bldev->device)
			return -ENODEV;
	}

	return 0;
}