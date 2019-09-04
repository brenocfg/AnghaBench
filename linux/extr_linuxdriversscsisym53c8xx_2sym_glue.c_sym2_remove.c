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
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  attach_count ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  sym_detach (struct Scsi_Host*,struct pci_dev*) ; 

__attribute__((used)) static void sym2_remove(struct pci_dev *pdev)
{
	struct Scsi_Host *shost = pci_get_drvdata(pdev);

	scsi_remove_host(shost);
	sym_detach(shost, pdev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);

	attach_count--;
}