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
struct pci_dev {int /*<<< orphan*/  dma_mask; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int fls64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static ssize_t dma_mask_bits_show(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	struct pci_dev *pdev = to_pci_dev(dev);

	return sprintf(buf, "%d\n", fls64(pdev->dma_mask));
}