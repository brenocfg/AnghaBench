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
typedef  int /*<<< orphan*/  ulong ;
struct msix_entry {int dummy; } ;
struct gasket_wire_interrupt_offsets {int dummy; } ;
struct gasket_interrupt_desc {int dummy; } ;
struct gasket_interrupt_data {char const* name; int type; int num_interrupts; int interrupt_bar_index; int pack_width; struct gasket_interrupt_data* msix_entries; struct gasket_interrupt_data* eventfd_ctxs; void* interrupt_counts; struct gasket_wire_interrupt_offsets const* wire_interrupt_offsets; scalar_t__ num_configured; struct gasket_interrupt_desc const* interrupts; int /*<<< orphan*/  pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct gasket_dev {TYPE_1__ dev_info; int /*<<< orphan*/  dev; int /*<<< orphan*/  pci_dev; struct gasket_interrupt_data* interrupt_data; } ;
struct eventfd_ctx {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  PCI_MSI 130 
#define  PCI_MSIX 129 
#define  PLATFORM_WIRE 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  force_msix_interrupt_unmasking (struct gasket_dev*) ; 
 int gasket_interrupt_msix_init (struct gasket_interrupt_data*) ; 
 int /*<<< orphan*/  gasket_interrupt_setup (struct gasket_dev*) ; 
 int /*<<< orphan*/  gasket_sysfs_create_entries (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interrupt_sysfs_attrs ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gasket_interrupt_data*) ; 
 struct gasket_interrupt_data* kzalloc (int,int /*<<< orphan*/ ) ; 

int gasket_interrupt_init(struct gasket_dev *gasket_dev, const char *name,
			  int type,
			  const struct gasket_interrupt_desc *interrupts,
			  int num_interrupts, int pack_width, int bar_index,
			  const struct gasket_wire_interrupt_offsets *wire_int_offsets)
{
	int ret;
	struct gasket_interrupt_data *interrupt_data;

	interrupt_data = kzalloc(sizeof(struct gasket_interrupt_data),
				 GFP_KERNEL);
	if (!interrupt_data)
		return -ENOMEM;
	gasket_dev->interrupt_data = interrupt_data;
	interrupt_data->name = name;
	interrupt_data->type = type;
	interrupt_data->pci_dev = gasket_dev->pci_dev;
	interrupt_data->num_interrupts = num_interrupts;
	interrupt_data->interrupts = interrupts;
	interrupt_data->interrupt_bar_index = bar_index;
	interrupt_data->pack_width = pack_width;
	interrupt_data->num_configured = 0;
	interrupt_data->wire_interrupt_offsets = wire_int_offsets;

	/* Allocate all dynamic structures. */
	interrupt_data->msix_entries = kcalloc(num_interrupts,
					       sizeof(struct msix_entry),
					       GFP_KERNEL);
	if (!interrupt_data->msix_entries) {
		kfree(interrupt_data);
		return -ENOMEM;
	}

	interrupt_data->eventfd_ctxs = kcalloc(num_interrupts,
					       sizeof(struct eventfd_ctx *),
					       GFP_KERNEL);
	if (!interrupt_data->eventfd_ctxs) {
		kfree(interrupt_data->msix_entries);
		kfree(interrupt_data);
		return -ENOMEM;
	}

	interrupt_data->interrupt_counts = kcalloc(num_interrupts,
						   sizeof(ulong),
						   GFP_KERNEL);
	if (!interrupt_data->interrupt_counts) {
		kfree(interrupt_data->eventfd_ctxs);
		kfree(interrupt_data->msix_entries);
		kfree(interrupt_data);
		return -ENOMEM;
	}

	switch (interrupt_data->type) {
	case PCI_MSIX:
		ret = gasket_interrupt_msix_init(interrupt_data);
		if (ret)
			break;
		force_msix_interrupt_unmasking(gasket_dev);
		break;

	case PCI_MSI:
	case PLATFORM_WIRE:
	default:
		dev_err(gasket_dev->dev,
			"Cannot handle unsupported interrupt type %d\n",
			interrupt_data->type);
		ret = -EINVAL;
	}

	if (ret) {
		/* Failing to setup interrupts will cause the device to report
		 * GASKET_STATUS_LAMED. But it is not fatal.
		 */
		dev_warn(gasket_dev->dev,
			 "Couldn't initialize interrupts: %d\n", ret);
		return 0;
	}

	gasket_interrupt_setup(gasket_dev);
	gasket_sysfs_create_entries(gasket_dev->dev_info.device,
				    interrupt_sysfs_attrs);

	return 0;
}