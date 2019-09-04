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
struct asd_ha_struct {int /*<<< orphan*/  pcidev; struct asd_ha_addrspace* io_handle; scalar_t__ iospace; } ;
struct asd_ha_addrspace {int /*<<< orphan*/  addr; int /*<<< orphan*/  len; int /*<<< orphan*/  start; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASD_DRIVER_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  asd_printk (char*,int,...) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_region (int /*<<< orphan*/ ,int) ; 
 int pci_request_region (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_flags (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int asd_map_memio(struct asd_ha_struct *asd_ha)
{
	int err, i;
	struct asd_ha_addrspace *io_handle;

	asd_ha->iospace = 0;
	for (i = 0; i < 3; i += 2) {
		io_handle = &asd_ha->io_handle[i==0?0:1];
		io_handle->start = pci_resource_start(asd_ha->pcidev, i);
		io_handle->len   = pci_resource_len(asd_ha->pcidev, i);
		io_handle->flags = pci_resource_flags(asd_ha->pcidev, i);
		err = -ENODEV;
		if (!io_handle->start || !io_handle->len) {
			asd_printk("MBAR%d start or length for %s is 0.\n",
				   i==0?0:1, pci_name(asd_ha->pcidev));
			goto Err;
		}
		err = pci_request_region(asd_ha->pcidev, i, ASD_DRIVER_NAME);
		if (err) {
			asd_printk("couldn't reserve memory region for %s\n",
				   pci_name(asd_ha->pcidev));
			goto Err;
		}
		io_handle->addr = ioremap(io_handle->start, io_handle->len);
		if (!io_handle->addr) {
			asd_printk("couldn't map MBAR%d of %s\n", i==0?0:1,
				   pci_name(asd_ha->pcidev));
			err = -ENOMEM;
			goto Err_unreq;
		}
	}

	return 0;
Err_unreq:
	pci_release_region(asd_ha->pcidev, i);
Err:
	if (i > 0) {
		io_handle = &asd_ha->io_handle[0];
		iounmap(io_handle->addr);
		pci_release_region(asd_ha->pcidev, 0);
	}
	return err;
}