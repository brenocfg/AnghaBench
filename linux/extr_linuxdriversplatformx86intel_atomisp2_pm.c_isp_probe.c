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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MBI_UNIT_PMC ; 
 int EBUSY ; 
 int /*<<< orphan*/  ISPSSPM0 ; 
 int /*<<< orphan*/  ISPSSPM0_ISPSSC_MASK ; 
 int ISPSSPM0_ISPSSS_MASK ; 
 int ISPSSPM0_ISPSSS_OFFSET ; 
 int ISPSSPM0_IUNIT_POWER_OFF ; 
 int /*<<< orphan*/  MBI_REG_READ ; 
 int /*<<< orphan*/  PCI_CSI_CONTROL ; 
 int PCI_CSI_CONTROL_PORTS_OFF_MASK ; 
 int /*<<< orphan*/  PCI_INTERRUPT_CTRL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iosf_mbi_modify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iosf_mbi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_allow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync_suspend (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int isp_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	unsigned long timeout;
	u32 val;

	pci_write_config_dword(dev, PCI_INTERRUPT_CTRL, 0);

	/*
	 * MRFLD IUNIT DPHY is located in an always-power-on island
	 * MRFLD HW design need all CSI ports are disabled before
	 * powering down the IUNIT.
	 */
	pci_read_config_dword(dev, PCI_CSI_CONTROL, &val);
	val |= PCI_CSI_CONTROL_PORTS_OFF_MASK;
	pci_write_config_dword(dev, PCI_CSI_CONTROL, val);

	/* Write 0x3 to ISPSSPM0 bit[1:0] to power off the IUNIT */
	iosf_mbi_modify(BT_MBI_UNIT_PMC, MBI_REG_READ, ISPSSPM0,
			ISPSSPM0_IUNIT_POWER_OFF, ISPSSPM0_ISPSSC_MASK);

	/*
	 * There should be no IUNIT access while power-down is
	 * in progress HW sighting: 4567865
	 * Wait up to 50 ms for the IUNIT to shut down.
	 */
	timeout = jiffies + msecs_to_jiffies(50);
	while (1) {
		/* Wait until ISPSSPM0 bit[25:24] shows 0x3 */
		iosf_mbi_read(BT_MBI_UNIT_PMC, MBI_REG_READ, ISPSSPM0, &val);
		val = (val & ISPSSPM0_ISPSSS_MASK) >> ISPSSPM0_ISPSSS_OFFSET;
		if (val == ISPSSPM0_IUNIT_POWER_OFF)
			break;

		if (time_after(jiffies, timeout)) {
			dev_err(&dev->dev, "IUNIT power-off timeout.\n");
			return -EBUSY;
		}
		usleep_range(1000, 2000);
	}

	pm_runtime_allow(&dev->dev);
	pm_runtime_put_sync_suspend(&dev->dev);

	return 0;
}