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
struct pvscsi_adapter {int dummy; } ;
struct pci_dev {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pvscsi_shutdown (struct pvscsi_adapter*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pvscsi_release_resources (struct pvscsi_adapter*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 struct pvscsi_adapter* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static void pvscsi_remove(struct pci_dev *pdev)
{
	struct Scsi_Host *host = pci_get_drvdata(pdev);
	struct pvscsi_adapter *adapter = shost_priv(host);

	scsi_remove_host(host);

	__pvscsi_shutdown(adapter);
	pvscsi_release_resources(adapter);

	scsi_host_put(host);

	pci_disable_device(pdev);
}