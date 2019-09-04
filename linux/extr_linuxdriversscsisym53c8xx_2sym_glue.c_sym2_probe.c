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
typedef  int /*<<< orphan*/  sym_dev ;
struct sym_nvram {int /*<<< orphan*/  host_id; struct pci_dev* pdev; } ;
struct sym_device {int /*<<< orphan*/  host_id; struct pci_dev* pdev; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  nvram ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  NAME53C8XX ; 
 int /*<<< orphan*/  SYM_SETUP_HOST_ID ; 
 int /*<<< orphan*/  attach_count ; 
 int /*<<< orphan*/  memset (struct sym_nvram*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 scalar_t__ pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 scalar_t__ scsi_add_host (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_scan_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  sym2_template ; 
 struct Scsi_Host* sym_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sym_nvram*) ; 
 scalar_t__ sym_check_raid (struct sym_nvram*) ; 
 scalar_t__ sym_check_supported (struct sym_nvram*) ; 
 int /*<<< orphan*/  sym_config_pqs (struct pci_dev*,struct sym_nvram*) ; 
 int /*<<< orphan*/  sym_detach (int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  sym_get_nvram (struct sym_nvram*,struct sym_nvram*) ; 
 scalar_t__ sym_iomap_device (struct sym_nvram*) ; 
 int /*<<< orphan*/  sym_iounmap_device (struct sym_nvram*) ; 
 scalar_t__ sym_set_workarounds (struct sym_nvram*) ; 

__attribute__((used)) static int sym2_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct sym_device sym_dev;
	struct sym_nvram nvram;
	struct Scsi_Host *shost;
	int do_iounmap = 0;
	int do_disable_device = 1;

	memset(&sym_dev, 0, sizeof(sym_dev));
	memset(&nvram, 0, sizeof(nvram));
	sym_dev.pdev = pdev;
	sym_dev.host_id = SYM_SETUP_HOST_ID;

	if (pci_enable_device(pdev))
		goto leave;

	pci_set_master(pdev);

	if (pci_request_regions(pdev, NAME53C8XX))
		goto disable;

	if (sym_check_supported(&sym_dev))
		goto free;

	if (sym_iomap_device(&sym_dev))
		goto free;
	do_iounmap = 1;

	if (sym_check_raid(&sym_dev)) {
		do_disable_device = 0;	/* Don't disable the device */
		goto free;
	}

	if (sym_set_workarounds(&sym_dev))
		goto free;

	sym_config_pqs(pdev, &sym_dev);

	sym_get_nvram(&sym_dev, &nvram);

	do_iounmap = 0; /* Don't sym_iounmap_device() after sym_attach(). */
	shost = sym_attach(&sym2_template, attach_count, &sym_dev);
	if (!shost)
		goto free;

	if (scsi_add_host(shost, &pdev->dev))
		goto detach;
	scsi_scan_host(shost);

	attach_count++;

	return 0;

 detach:
	sym_detach(pci_get_drvdata(pdev), pdev);
 free:
	if (do_iounmap)
		sym_iounmap_device(&sym_dev);
	pci_release_regions(pdev);
 disable:
	if (do_disable_device)
		pci_disable_device(pdev);
 leave:
	return -ENODEV;
}