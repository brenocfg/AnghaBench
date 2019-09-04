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
struct atp_unit {struct Scsi_Host* host; } ;
struct Scsi_Host {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  atp870u_free_tables (struct Scsi_Host*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct Scsi_Host*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct atp_unit* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 

__attribute__((used)) static void atp870u_remove (struct pci_dev *pdev)
{	
	struct atp_unit *devext = pci_get_drvdata(pdev);
	struct Scsi_Host *pshost = devext->host;
	
	
	scsi_remove_host(pshost);
	free_irq(pshost->irq, pshost);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	atp870u_free_tables(pshost);
	scsi_host_put(pshost);
}