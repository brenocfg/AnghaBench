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
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int,int) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

void sb800_prefetch(struct device *dev, int on)
{
	u16 misc;
	struct pci_dev *pdev = to_pci_dev(dev);

	pci_read_config_word(pdev, 0x50, &misc);
	if (on == 0)
		pci_write_config_word(pdev, 0x50, misc & 0xfcff);
	else
		pci_write_config_word(pdev, 0x50, misc | 0x0300);
}