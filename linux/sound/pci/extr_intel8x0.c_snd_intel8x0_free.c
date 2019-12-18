#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ area; } ;
struct intel8x0 {scalar_t__ irq; unsigned int bdbars_count; scalar_t__ device_type; int /*<<< orphan*/  pci; scalar_t__ bmaddr; scalar_t__ addr; TYPE_2__ bdbars; TYPE_1__* ichd; } ;
struct TYPE_3__ {scalar_t__ reg_offset; } ;

/* Variables and functions */
 scalar_t__ DEVICE_NFORCE ; 
 scalar_t__ ICH_REG_OFF_CR ; 
 int ICH_RESETREGS ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct intel8x0*) ; 
 int /*<<< orphan*/  iputbyte (struct intel8x0*,scalar_t__,int) ; 
 int /*<<< orphan*/  kfree (struct intel8x0*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_2__*) ; 
 int /*<<< orphan*/  spdif_aclink ; 

__attribute__((used)) static int snd_intel8x0_free(struct intel8x0 *chip)
{
	unsigned int i;

	if (chip->irq < 0)
		goto __hw_end;
	/* disable interrupts */
	for (i = 0; i < chip->bdbars_count; i++)
		iputbyte(chip, ICH_REG_OFF_CR + chip->ichd[i].reg_offset, 0x00);
	/* reset channels */
	for (i = 0; i < chip->bdbars_count; i++)
		iputbyte(chip, ICH_REG_OFF_CR + chip->ichd[i].reg_offset, ICH_RESETREGS);
	if (chip->device_type == DEVICE_NFORCE && !spdif_aclink) {
		/* stop the spdif interrupt */
		unsigned int val;
		pci_read_config_dword(chip->pci, 0x4c, &val);
		val &= ~0x1000000;
		pci_write_config_dword(chip->pci, 0x4c, val);
	}
	/* --- */

      __hw_end:
	if (chip->irq >= 0)
		free_irq(chip->irq, chip);
	if (chip->bdbars.area)
		snd_dma_free_pages(&chip->bdbars);
	if (chip->addr)
		pci_iounmap(chip->pci, chip->addr);
	if (chip->bmaddr)
		pci_iounmap(chip->pci, chip->bmaddr);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kfree(chip);
	return 0;
}