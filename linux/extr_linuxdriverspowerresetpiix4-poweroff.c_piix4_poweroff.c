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
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DEVFN (int,int) ; 
 int PCI_DEVID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PIIX4_FUNC3IO_PMCNTRL ; 
 int PIIX4_FUNC3IO_PMCNTRL_SUS_EN ; 
 int PIIX4_FUNC3IO_PMCNTRL_SUS_TYP_SOFF ; 
 scalar_t__ PIIX4_FUNC3IO_PMSTS ; 
 int PIIX4_FUNC3IO_PMSTS_PWRBTN_STS ; 
 int /*<<< orphan*/  PIIX4_SUSPEND_MAGIC ; 
 int inw (scalar_t__) ; 
 scalar_t__ io_offset ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  pci_bus_write_config_dword (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* pm_dev ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 

__attribute__((used)) static void piix4_poweroff(void)
{
	int spec_devid;
	u16 sts;

	/* Ensure the power button status is clear */
	while (1) {
		sts = inw(io_offset + PIIX4_FUNC3IO_PMSTS);
		if (!(sts & PIIX4_FUNC3IO_PMSTS_PWRBTN_STS))
			break;
		outw(sts, io_offset + PIIX4_FUNC3IO_PMSTS);
	}

	/* Enable entry to suspend */
	outw(PIIX4_FUNC3IO_PMCNTRL_SUS_TYP_SOFF | PIIX4_FUNC3IO_PMCNTRL_SUS_EN,
	     io_offset + PIIX4_FUNC3IO_PMCNTRL);

	/* If the special cycle occurs too soon this doesn't work... */
	mdelay(10);

	/*
	 * The PIIX4 will enter the suspend state only after seeing a special
	 * cycle with the correct magic data on the PCI bus. Generate that
	 * cycle now.
	 */
	spec_devid = PCI_DEVID(0, PCI_DEVFN(0x1f, 0x7));
	pci_bus_write_config_dword(pm_dev->bus, spec_devid, 0,
				   PIIX4_SUSPEND_MAGIC);

	/* Give the system some time to power down, then error */
	mdelay(1000);
	pr_emerg("Unable to poweroff system\n");
}