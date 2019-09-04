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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ips_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ips_ha ; 
 scalar_t__ ips_hotplug ; 
 int ips_init_phase1 (struct pci_dev*,int*) ; 
 int ips_init_phase2 (int) ; 
 scalar_t__ ips_next_controller ; 
 scalar_t__ ips_num_controllers ; 
 scalar_t__ ips_register_scsi (int) ; 
 int /*<<< orphan*/ * ips_sh ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ips_insert_device(struct pci_dev *pci_dev, const struct pci_device_id *ent)
{
	int index = -1;
	int rc;

	METHOD_TRACE("ips_insert_device", 1);
	rc = pci_enable_device(pci_dev);
	if (rc)
		return rc;

	rc = pci_request_regions(pci_dev, "ips");
	if (rc)
		goto err_out;

	rc = ips_init_phase1(pci_dev, &index);
	if (rc == SUCCESS)
		rc = ips_init_phase2(index);

	if (ips_hotplug)
		if (ips_register_scsi(index)) {
			ips_free(ips_ha[index]);
			rc = -1;
		}

	if (rc == SUCCESS)
		ips_num_controllers++;

	ips_next_controller = ips_num_controllers;

	if (rc < 0) {
		rc = -ENODEV;
		goto err_out_regions;
	}

	pci_set_drvdata(pci_dev, ips_sh[index]);
	return 0;

err_out_regions:
	pci_release_regions(pci_dev);
err_out:
	pci_disable_device(pci_dev);
	return rc;
}