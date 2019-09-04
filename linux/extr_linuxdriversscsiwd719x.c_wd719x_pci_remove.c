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
struct wd719x {int /*<<< orphan*/  base; } ;
struct pci_dev {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 struct wd719x* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  wd719x_destroy (struct wd719x*) ; 

__attribute__((used)) static void wd719x_pci_remove(struct pci_dev *pdev)
{
	struct Scsi_Host *sh = pci_get_drvdata(pdev);
	struct wd719x *wd = shost_priv(sh);

	scsi_remove_host(sh);
	wd719x_destroy(wd);
	pci_iounmap(pdev, wd->base);
	pci_release_regions(pdev);
	pci_disable_device(pdev);

	scsi_host_put(sh);
}