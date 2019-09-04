#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct physdev_pci_device_add {int is_extfn; int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; int /*<<< orphan*/  flags; scalar_t__ seg; } ;
struct physdev_manage_pci_ext {int is_extfn; int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; int /*<<< orphan*/  flags; scalar_t__ seg; } ;
struct physdev_manage_pci {int is_extfn; int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; int /*<<< orphan*/  flags; scalar_t__ seg; } ;
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int ENOSYS ; 
 int HYPERVISOR_physdev_op (int /*<<< orphan*/ ,struct physdev_pci_device_add*) ; 
 scalar_t__ PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHYSDEVOP_manage_pci_add ; 
 int /*<<< orphan*/  PHYSDEVOP_manage_pci_add_ext ; 
 int /*<<< orphan*/  PHYSDEVOP_pci_device_add ; 
 int /*<<< orphan*/  XEN_PCI_DEV_EXTFN ; 
 scalar_t__ pci_ari_enabled (TYPE_1__*) ; 
 scalar_t__ pci_domain_nr (TYPE_1__*) ; 
 int pci_seg_supported ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int xen_add_device(struct device *dev)
{
	int r;
	struct pci_dev *pci_dev = to_pci_dev(dev);
#ifdef CONFIG_PCI_IOV
	struct pci_dev *physfn = pci_dev->physfn;
#endif

	if (pci_seg_supported) {
		struct {
			struct physdev_pci_device_add add;
			uint32_t pxm;
		} add_ext = {
			.add.seg = pci_domain_nr(pci_dev->bus),
			.add.bus = pci_dev->bus->number,
			.add.devfn = pci_dev->devfn
		};
		struct physdev_pci_device_add *add = &add_ext.add;

#ifdef CONFIG_ACPI
		acpi_handle handle;
#endif

#ifdef CONFIG_PCI_IOV
		if (pci_dev->is_virtfn) {
			add->flags = XEN_PCI_DEV_VIRTFN;
			add->physfn.bus = physfn->bus->number;
			add->physfn.devfn = physfn->devfn;
		} else
#endif
		if (pci_ari_enabled(pci_dev->bus) && PCI_SLOT(pci_dev->devfn))
			add->flags = XEN_PCI_DEV_EXTFN;

#ifdef CONFIG_ACPI
		handle = ACPI_HANDLE(&pci_dev->dev);
#ifdef CONFIG_PCI_IOV
		if (!handle && pci_dev->is_virtfn)
			handle = ACPI_HANDLE(physfn->bus->bridge);
#endif
		if (!handle) {
			/*
			 * This device was not listed in the ACPI name space at
			 * all. Try to get acpi handle of parent pci bus.
			 */
			struct pci_bus *pbus;
			for (pbus = pci_dev->bus; pbus; pbus = pbus->parent) {
				handle = acpi_pci_get_bridge_handle(pbus);
				if (handle)
					break;
			}
		}
		if (handle) {
			acpi_status status;

			do {
				unsigned long long pxm;

				status = acpi_evaluate_integer(handle, "_PXM",
							       NULL, &pxm);
				if (ACPI_SUCCESS(status)) {
					add->optarr[0] = pxm;
					add->flags |= XEN_PCI_DEV_PXM;
					break;
				}
				status = acpi_get_parent(handle, &handle);
			} while (ACPI_SUCCESS(status));
		}
#endif /* CONFIG_ACPI */

		r = HYPERVISOR_physdev_op(PHYSDEVOP_pci_device_add, add);
		if (r != -ENOSYS)
			return r;
		pci_seg_supported = false;
	}

	if (pci_domain_nr(pci_dev->bus))
		r = -ENOSYS;
#ifdef CONFIG_PCI_IOV
	else if (pci_dev->is_virtfn) {
		struct physdev_manage_pci_ext manage_pci_ext = {
			.bus		= pci_dev->bus->number,
			.devfn		= pci_dev->devfn,
			.is_virtfn 	= 1,
			.physfn.bus	= physfn->bus->number,
			.physfn.devfn	= physfn->devfn,
		};

		r = HYPERVISOR_physdev_op(PHYSDEVOP_manage_pci_add_ext,
			&manage_pci_ext);
	}
#endif
	else if (pci_ari_enabled(pci_dev->bus) && PCI_SLOT(pci_dev->devfn)) {
		struct physdev_manage_pci_ext manage_pci_ext = {
			.bus		= pci_dev->bus->number,
			.devfn		= pci_dev->devfn,
			.is_extfn	= 1,
		};

		r = HYPERVISOR_physdev_op(PHYSDEVOP_manage_pci_add_ext,
			&manage_pci_ext);
	} else {
		struct physdev_manage_pci manage_pci = {
			.bus	= pci_dev->bus->number,
			.devfn	= pci_dev->devfn,
		};

		r = HYPERVISOR_physdev_op(PHYSDEVOP_manage_pci_add,
			&manage_pci);
	}

	return r;
}