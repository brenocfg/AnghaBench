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
typedef  int u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int IDT_BARSETUP_EN ; 
 int IDT_BARSETUP_MODE_CFG ; 
 int IDT_BARSETUP_SIZE_CFG ; 
 int IDT_BARSETUP_SIZE_MASK ; 
 int /*<<< orphan*/  IDT_NT_BARSETUP0 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int idt_check_setup(struct pci_dev *pdev)
{
	u32 data;
	int ret;

	/* Read the BARSETUP0 */
	ret = pci_read_config_dword(pdev, IDT_NT_BARSETUP0, &data);
	if (ret != 0) {
		dev_err(&pdev->dev,
			"Failed to read BARSETUP0 config register");
		return ret;
	}

	/* Check whether the BAR0 register is enabled to be of config space */
	if (!(data & IDT_BARSETUP_EN) || !(data & IDT_BARSETUP_MODE_CFG)) {
		dev_err(&pdev->dev, "BAR0 doesn't map config space");
		return -EINVAL;
	}

	/* Configuration space BAR0 must have certain size */
	if ((data & IDT_BARSETUP_SIZE_MASK) != IDT_BARSETUP_SIZE_CFG) {
		dev_err(&pdev->dev, "Invalid size of config space");
		return -EINVAL;
	}

	dev_dbg(&pdev->dev, "NTB device pre-initialized correctly");

	return 0;
}