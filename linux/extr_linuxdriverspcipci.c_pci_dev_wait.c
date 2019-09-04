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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int ENOTTY ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,int,char*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_warn (struct pci_dev*,char*,int,char*) ; 

__attribute__((used)) static int pci_dev_wait(struct pci_dev *dev, char *reset_type, int timeout)
{
	int delay = 1;
	u32 id;

	/*
	 * After reset, the device should not silently discard config
	 * requests, but it may still indicate that it needs more time by
	 * responding to them with CRS completions.  The Root Port will
	 * generally synthesize ~0 data to complete the read (except when
	 * CRS SV is enabled and the read was for the Vendor ID; in that
	 * case it synthesizes 0x0001 data).
	 *
	 * Wait for the device to return a non-CRS completion.  Read the
	 * Command register instead of Vendor ID so we don't have to
	 * contend with the CRS SV value.
	 */
	pci_read_config_dword(dev, PCI_COMMAND, &id);
	while (id == ~0) {
		if (delay > timeout) {
			pci_warn(dev, "not ready %dms after %s; giving up\n",
				 delay - 1, reset_type);
			return -ENOTTY;
		}

		if (delay > 1000)
			pci_info(dev, "not ready %dms after %s; waiting\n",
				 delay - 1, reset_type);

		msleep(delay);
		delay *= 2;
		pci_read_config_dword(dev, PCI_COMMAND, &id);
	}

	if (delay > 1000)
		pci_info(dev, "ready %dms after %s\n", delay - 1,
			 reset_type);

	return 0;
}