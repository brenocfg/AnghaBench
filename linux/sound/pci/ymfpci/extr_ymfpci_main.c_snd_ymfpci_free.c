#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ area; } ;
struct snd_ymfpci {scalar_t__ irq; int /*<<< orphan*/  controller_microcode; int /*<<< orphan*/  dsp_microcode; int /*<<< orphan*/  pci; int /*<<< orphan*/  old_legacy_ctrl; scalar_t__ res_reg_area; TYPE_1__ work_ptr; int /*<<< orphan*/  reg_area_virt; scalar_t__ fm_res; scalar_t__ mpu_res; struct snd_ymfpci* saved_regs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  YDSXGR_BUF441OUTVOL ; 
 int /*<<< orphan*/  YDSXGR_EFFCTRLBASE ; 
 int /*<<< orphan*/  YDSXGR_GLOBALCTRL ; 
 int /*<<< orphan*/  YDSXGR_LEGACYOUTVOL ; 
 int /*<<< orphan*/  YDSXGR_NATIVEDACOUTVOL ; 
 int /*<<< orphan*/  YDSXGR_PLAYCTRLBASE ; 
 int /*<<< orphan*/  YDSXGR_RECCTRLBASE ; 
 int /*<<< orphan*/  YDSXGR_STATUS ; 
 int /*<<< orphan*/  YDSXGR_WORKBASE ; 
 int /*<<< orphan*/  YDSXGR_WORKSIZE ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_ymfpci*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_ymfpci*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_power_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_and_free_resource (scalar_t__) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_ymfpci_ac3_done (struct snd_ymfpci*) ; 
 int /*<<< orphan*/  snd_ymfpci_disable_dsp (struct snd_ymfpci*) ; 
 int /*<<< orphan*/  snd_ymfpci_free_gameport (struct snd_ymfpci*) ; 
 int snd_ymfpci_readw (struct snd_ymfpci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ymfpci_writel (struct snd_ymfpci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ymfpci_writew (struct snd_ymfpci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int snd_ymfpci_free(struct snd_ymfpci *chip)
{
	u16 ctrl;

	if (snd_BUG_ON(!chip))
		return -EINVAL;

	if (chip->res_reg_area) {	/* don't touch busy hardware */
		snd_ymfpci_writel(chip, YDSXGR_NATIVEDACOUTVOL, 0);
		snd_ymfpci_writel(chip, YDSXGR_BUF441OUTVOL, 0);
		snd_ymfpci_writel(chip, YDSXGR_LEGACYOUTVOL, 0);
		snd_ymfpci_writel(chip, YDSXGR_STATUS, ~0);
		snd_ymfpci_disable_dsp(chip);
		snd_ymfpci_writel(chip, YDSXGR_PLAYCTRLBASE, 0);
		snd_ymfpci_writel(chip, YDSXGR_RECCTRLBASE, 0);
		snd_ymfpci_writel(chip, YDSXGR_EFFCTRLBASE, 0);
		snd_ymfpci_writel(chip, YDSXGR_WORKBASE, 0);
		snd_ymfpci_writel(chip, YDSXGR_WORKSIZE, 0);
		ctrl = snd_ymfpci_readw(chip, YDSXGR_GLOBALCTRL);
		snd_ymfpci_writew(chip, YDSXGR_GLOBALCTRL, ctrl & ~0x0007);
	}

	snd_ymfpci_ac3_done(chip);

	/* Set PCI device to D3 state */
#if 0
	/* FIXME: temporarily disabled, otherwise we cannot fire up
	 * the chip again unless reboot.  ACPI bug?
	 */
	pci_set_power_state(chip->pci, PCI_D3hot);
#endif

#ifdef CONFIG_PM_SLEEP
	kfree(chip->saved_regs);
#endif
	if (chip->irq >= 0)
		free_irq(chip->irq, chip);
	release_and_free_resource(chip->mpu_res);
	release_and_free_resource(chip->fm_res);
	snd_ymfpci_free_gameport(chip);
	iounmap(chip->reg_area_virt);
	if (chip->work_ptr.area)
		snd_dma_free_pages(&chip->work_ptr);
	
	release_and_free_resource(chip->res_reg_area);

	pci_write_config_word(chip->pci, 0x40, chip->old_legacy_ctrl);
	
	pci_disable_device(chip->pci);
	release_firmware(chip->dsp_microcode);
	release_firmware(chip->controller_microcode);
	kfree(chip);
	return 0;
}