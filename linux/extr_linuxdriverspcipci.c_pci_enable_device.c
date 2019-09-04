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

/* Variables and functions */
 int IORESOURCE_IO ; 
 int IORESOURCE_MEM ; 
 int pci_enable_device_flags (struct pci_dev*,int) ; 

int pci_enable_device(struct pci_dev *dev)
{
	return pci_enable_device_flags(dev, IORESOURCE_MEM | IORESOURCE_IO);
}