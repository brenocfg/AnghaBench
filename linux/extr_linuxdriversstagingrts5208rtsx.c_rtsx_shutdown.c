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
struct rtsx_dev {int irq; struct rtsx_chip* chip; } ;
struct rtsx_chip {scalar_t__ msi_en; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM_S1 ; 
 int /*<<< orphan*/  free_irq (int,void*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 struct rtsx_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  rtsx_do_before_power_down (struct rtsx_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtsx_shutdown(struct pci_dev *pci)
{
	struct rtsx_dev *dev = pci_get_drvdata(pci);
	struct rtsx_chip *chip;

	if (!dev)
		return;

	chip = dev->chip;

	rtsx_do_before_power_down(chip, PM_S1);

	if (dev->irq >= 0) {
		free_irq(dev->irq, (void *)dev);
		dev->irq = -1;
	}

	if (chip->msi_en)
		pci_disable_msi(pci);

	pci_disable_device(pci);
}