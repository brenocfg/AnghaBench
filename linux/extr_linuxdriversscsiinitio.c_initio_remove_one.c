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
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct initio_host {int /*<<< orphan*/  addr; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct Scsi_Host*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 

__attribute__((used)) static void initio_remove_one(struct pci_dev *pdev)
{
	struct Scsi_Host *host = pci_get_drvdata(pdev);
	struct initio_host *s = (struct initio_host *)host->hostdata;
	scsi_remove_host(host);
	free_irq(pdev->irq, host);
	release_region(s->addr, 256);
	scsi_host_put(host);
	pci_disable_device(pdev);
}