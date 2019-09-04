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
struct pci_device_id {int dummy; } ;
struct pci_dev {scalar_t__ device; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct asc_board {int /*<<< orphan*/  flags; struct Scsi_Host* shost; int /*<<< orphan*/ * dev; int /*<<< orphan*/  irq; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASC_IS_PCI ; 
 int /*<<< orphan*/  ASC_IS_WIDE_BOARD ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ PCI_DEVICE_ID_38C0800_REV1 ; 
 scalar_t__ PCI_DEVICE_ID_38C1600_REV1 ; 
 scalar_t__ PCI_DEVICE_ID_ASP_ABP940UW ; 
 int advansys_board_found (struct Scsi_Host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  advansys_set_latency (struct pci_dev*) ; 
 int /*<<< orphan*/  advansys_template ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct Scsi_Host*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 struct Scsi_Host* scsi_host_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 struct asc_board* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int advansys_pci_probe(struct pci_dev *pdev,
			      const struct pci_device_id *ent)
{
	int err, ioport;
	struct Scsi_Host *shost;
	struct asc_board *board;

	err = pci_enable_device(pdev);
	if (err)
		goto fail;
	err = pci_request_regions(pdev, DRV_NAME);
	if (err)
		goto disable_device;
	pci_set_master(pdev);
	advansys_set_latency(pdev);

	err = -ENODEV;
	if (pci_resource_len(pdev, 0) == 0)
		goto release_region;

	ioport = pci_resource_start(pdev, 0);

	err = -ENOMEM;
	shost = scsi_host_alloc(&advansys_template, sizeof(*board));
	if (!shost)
		goto release_region;

	board = shost_priv(shost);
	board->irq = pdev->irq;
	board->dev = &pdev->dev;
	board->shost = shost;

	if (pdev->device == PCI_DEVICE_ID_ASP_ABP940UW ||
	    pdev->device == PCI_DEVICE_ID_38C0800_REV1 ||
	    pdev->device == PCI_DEVICE_ID_38C1600_REV1) {
		board->flags |= ASC_IS_WIDE_BOARD;
	}

	err = advansys_board_found(shost, ioport, ASC_IS_PCI);
	if (err)
		goto free_host;

	pci_set_drvdata(pdev, shost);
	return 0;

 free_host:
	scsi_host_put(shost);
 release_region:
	pci_release_regions(pdev);
 disable_device:
	pci_disable_device(pdev);
 fail:
	return err;
}