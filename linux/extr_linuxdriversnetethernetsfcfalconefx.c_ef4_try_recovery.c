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
struct ef4_nic {int dummy; } ;

/* Variables and functions */

int ef4_try_recovery(struct ef4_nic *efx)
{
#ifdef CONFIG_EEH
	/* A PCI error can occur and not be seen by EEH because nothing
	 * happens on the PCI bus. In this case the driver may fail and
	 * schedule a 'recover or reset', leading to this recovery handler.
	 * Manually call the eeh failure check function.
	 */
	struct eeh_dev *eehdev = pci_dev_to_eeh_dev(efx->pci_dev);
	if (eeh_dev_check_failure(eehdev)) {
		/* The EEH mechanisms will handle the error and reset the
		 * device if necessary.
		 */
		return 1;
	}
#endif
	return 0;
}