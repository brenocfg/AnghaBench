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
struct pci_dev {int dummy; } ;
typedef  scalar_t__ pci_ers_result_t ;
typedef  enum pci_channel_state { ____Placeholder_pci_channel_state } pci_channel_state ;

/* Variables and functions */
 scalar_t__ PCI_ERS_RESULT_CAN_RECOVER ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 scalar_t__ PCI_ERS_RESULT_NEED_RESET ; 
 scalar_t__ PCI_ERS_RESULT_RECOVERED ; 
 scalar_t__ broadcast_error_message (struct pci_dev*,int,char*,int /*<<< orphan*/ ) ; 
 int pci_channel_io_normal ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_uevent_ers (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_error_detected ; 
 int /*<<< orphan*/  report_mmio_enabled ; 
 int /*<<< orphan*/  report_resume ; 
 int /*<<< orphan*/  report_slot_reset ; 

void pcie_do_nonfatal_recovery(struct pci_dev *dev)
{
	pci_ers_result_t status;
	enum pci_channel_state state;

	state = pci_channel_io_normal;

	status = broadcast_error_message(dev,
			state,
			"error_detected",
			report_error_detected);

	if (status == PCI_ERS_RESULT_CAN_RECOVER)
		status = broadcast_error_message(dev,
				state,
				"mmio_enabled",
				report_mmio_enabled);

	if (status == PCI_ERS_RESULT_NEED_RESET) {
		/*
		 * TODO: Should call platform-specific
		 * functions to reset slot before calling
		 * drivers' slot_reset callbacks?
		 */
		status = broadcast_error_message(dev,
				state,
				"slot_reset",
				report_slot_reset);
	}

	if (status != PCI_ERS_RESULT_RECOVERED)
		goto failed;

	broadcast_error_message(dev,
				state,
				"resume",
				report_resume);

	pci_info(dev, "AER: Device recovery successful\n");
	return;

failed:
	pci_uevent_ers(dev, PCI_ERS_RESULT_DISCONNECT);

	/* TODO: Should kernel panic here? */
	pci_info(dev, "AER: Device recovery failed\n");
}