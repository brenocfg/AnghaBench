#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {size_t driver_data; } ;
struct TYPE_2__ {int size; int /*<<< orphan*/  virtual; void* physical; } ;
struct i810fb_par {int /*<<< orphan*/  mmio_start_virtual; void* mmio_start_phys; int /*<<< orphan*/  res_flags; TYPE_1__ aperture; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FRAMEBUFFER_REQ ; 
 int /*<<< orphan*/  MMIO_REQ ; 
 int MMIO_SIZE ; 
 int /*<<< orphan*/  PCI_DEVICE_ENABLED ; 
 int /*<<< orphan*/ * i810_pci_list ; 
 int /*<<< orphan*/  ioremap_nocache (void*,int) ; 
 int /*<<< orphan*/  ioremap_wc (void*,int) ; 
 int pci_enable_device (int /*<<< orphan*/ ) ; 
 int pci_resource_len (int /*<<< orphan*/ ,int) ; 
 void* pci_resource_start (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  request_mem_region (void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i810_allocate_pci_resource(struct i810fb_par *par,
				      const struct pci_device_id *entry)
{
	int err;

	if ((err = pci_enable_device(par->dev))) { 
		printk("i810fb_init: cannot enable device\n");
		return err;		
	}
	par->res_flags |= PCI_DEVICE_ENABLED;

	if (pci_resource_len(par->dev, 0) > 512 * 1024) {
		par->aperture.physical = pci_resource_start(par->dev, 0);
		par->aperture.size = pci_resource_len(par->dev, 0);
		par->mmio_start_phys = pci_resource_start(par->dev, 1);
	} else {
		par->aperture.physical = pci_resource_start(par->dev, 1);
		par->aperture.size = pci_resource_len(par->dev, 1);
		par->mmio_start_phys = pci_resource_start(par->dev, 0);
	}
	if (!par->aperture.size) {
		printk("i810fb_init: device is disabled\n");
		return -ENOMEM;
	}

	if (!request_mem_region(par->aperture.physical, 
				par->aperture.size, 
				i810_pci_list[entry->driver_data])) {
		printk("i810fb_init: cannot request framebuffer region\n");
		return -ENODEV;
	}
	par->res_flags |= FRAMEBUFFER_REQ;

	par->aperture.virtual = ioremap_wc(par->aperture.physical,
					   par->aperture.size);
	if (!par->aperture.virtual) {
		printk("i810fb_init: cannot remap framebuffer region\n");
		return -ENODEV;
	}
  
	if (!request_mem_region(par->mmio_start_phys, 
				MMIO_SIZE, 
				i810_pci_list[entry->driver_data])) {
		printk("i810fb_init: cannot request mmio region\n");
		return -ENODEV;
	}
	par->res_flags |= MMIO_REQ;

	par->mmio_start_virtual = ioremap_nocache(par->mmio_start_phys, 
						  MMIO_SIZE);
	if (!par->mmio_start_virtual) {
		printk("i810fb_init: cannot remap mmio region\n");
		return -ENODEV;
	}

	return 0;
}