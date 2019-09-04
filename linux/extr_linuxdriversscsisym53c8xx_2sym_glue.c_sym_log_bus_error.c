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
struct sym_data {struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  PCI_STATUS ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,unsigned short*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*,unsigned short) ; 
 struct sym_data* shost_priv (struct Scsi_Host*) ; 

void sym_log_bus_error(struct Scsi_Host *shost)
{
	struct sym_data *sym_data = shost_priv(shost);
	struct pci_dev *pdev = sym_data->pdev;
	unsigned short pci_sts;
	pci_read_config_word(pdev, PCI_STATUS, &pci_sts);
	if (pci_sts & 0xf900) {
		pci_write_config_word(pdev, PCI_STATUS, pci_sts);
		shost_printk(KERN_WARNING, shost,
			"PCI bus error: status = 0x%04x\n", pci_sts & 0xf900);
	}
}