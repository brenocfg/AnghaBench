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
struct pci_dev {int device; scalar_t__ msix_cap; } ;

/* Variables and functions */
 int ENOTTY ; 
 scalar_t__ PCI_COMMAND ; 
 int PCI_COMMAND_MASTER ; 
 scalar_t__ PCI_MSIX_FLAGS ; 
 int PCI_MSIX_FLAGS_ENABLE ; 
 int PCI_MSIX_FLAGS_MASKALL ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  pcie_flr (struct pci_dev*) ; 

__attribute__((used)) static int reset_chelsio_generic_dev(struct pci_dev *dev, int probe)
{
	u16 old_command;
	u16 msix_flags;

	/*
	 * If this isn't a Chelsio T4-based device, return -ENOTTY indicating
	 * that we have no device-specific reset method.
	 */
	if ((dev->device & 0xf000) != 0x4000)
		return -ENOTTY;

	/*
	 * If this is the "probe" phase, return 0 indicating that we can
	 * reset this device.
	 */
	if (probe)
		return 0;

	/*
	 * T4 can wedge if there are DMAs in flight within the chip and Bus
	 * Master has been disabled.  We need to have it on till the Function
	 * Level Reset completes.  (BUS_MASTER is disabled in
	 * pci_reset_function()).
	 */
	pci_read_config_word(dev, PCI_COMMAND, &old_command);
	pci_write_config_word(dev, PCI_COMMAND,
			      old_command | PCI_COMMAND_MASTER);

	/*
	 * Perform the actual device function reset, saving and restoring
	 * configuration information around the reset.
	 */
	pci_save_state(dev);

	/*
	 * T4 also suffers a Head-Of-Line blocking problem if MSI-X interrupts
	 * are disabled when an MSI-X interrupt message needs to be delivered.
	 * So we briefly re-enable MSI-X interrupts for the duration of the
	 * FLR.  The pci_restore_state() below will restore the original
	 * MSI-X state.
	 */
	pci_read_config_word(dev, dev->msix_cap+PCI_MSIX_FLAGS, &msix_flags);
	if ((msix_flags & PCI_MSIX_FLAGS_ENABLE) == 0)
		pci_write_config_word(dev, dev->msix_cap+PCI_MSIX_FLAGS,
				      msix_flags |
				      PCI_MSIX_FLAGS_ENABLE |
				      PCI_MSIX_FLAGS_MASKALL);

	pcie_flr(dev);

	/*
	 * Restore the configuration information (BAR values, etc.) including
	 * the original PCI Configuration Space Command word, and return
	 * success.
	 */
	pci_restore_state(dev);
	pci_write_config_word(dev, PCI_COMMAND, old_command);
	return 0;
}