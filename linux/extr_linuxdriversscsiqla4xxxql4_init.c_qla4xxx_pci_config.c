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
typedef  int uint16_t ;
struct scsi_qla_host {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_INTX_DISABLE ; 
 int PCI_COMMAND_PARITY ; 
 int PCI_COMMAND_SERR ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 
 int pci_set_mwi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*) ; 

void qla4xxx_pci_config(struct scsi_qla_host *ha)
{
	uint16_t w;
	int status;

	ql4_printk(KERN_INFO, ha, "Configuring PCI space...\n");

	pci_set_master(ha->pdev);
	status = pci_set_mwi(ha->pdev);
	/*
	 * We want to respect framework's setting of PCI configuration space
	 * command register and also want to make sure that all bits of
	 * interest to us are properly set in command register.
	 */
	pci_read_config_word(ha->pdev, PCI_COMMAND, &w);
	w |= PCI_COMMAND_PARITY | PCI_COMMAND_SERR;
	w &= ~PCI_COMMAND_INTX_DISABLE;
	pci_write_config_word(ha->pdev, PCI_COMMAND, w);
}