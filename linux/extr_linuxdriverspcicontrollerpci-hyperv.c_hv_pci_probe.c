#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hv_vmbus_device_id {int dummy; } ;
struct TYPE_6__ {int domain; int /*<<< orphan*/  fwnode; } ;
struct hv_pcibus_device {int /*<<< orphan*/  wq; int /*<<< orphan*/  cfg_addr; TYPE_3__ sysdata; int /*<<< orphan*/  irq_domain; int /*<<< orphan*/  state; TYPE_2__* mem_config; int /*<<< orphan*/  remove_event; int /*<<< orphan*/  retarget_msi_interrupt_lock; int /*<<< orphan*/  device_list_lock; int /*<<< orphan*/  config_lock; int /*<<< orphan*/  resources_for_children; int /*<<< orphan*/  dr_list; int /*<<< orphan*/  children; int /*<<< orphan*/  remove_lock; struct hv_device* hdev; } ;
struct TYPE_4__ {int* b; } ;
struct hv_device {int /*<<< orphan*/  channel; int /*<<< orphan*/  device; TYPE_1__ dev_instance; } ;
struct TYPE_5__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_CONFIG_MMIO_LENGTH ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ,int) ; 
 int create_root_hv_pci_bus (struct hv_pcibus_device*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int hv_allocate_config_window (struct hv_pcibus_device*) ; 
 int /*<<< orphan*/  hv_free_config_window (struct hv_pcibus_device*) ; 
 int hv_pci_allocate_bridge_windows (struct hv_pcibus_device*) ; 
 int hv_pci_enter_d0 (struct hv_device*) ; 
 int /*<<< orphan*/  hv_pci_free_bridge_windows (struct hv_pcibus_device*) ; 
 int /*<<< orphan*/  hv_pci_onchannelcallback ; 
 int hv_pci_protocol_negotiation (struct hv_device*) ; 
 int hv_pci_query_relations (struct hv_device*) ; 
 int /*<<< orphan*/  hv_pcibus_init ; 
 int /*<<< orphan*/  hv_pcibus_probed ; 
 int hv_pcie_init_irq_domain (struct hv_pcibus_device*) ; 
 int hv_send_resources_allocated (struct hv_device*) ; 
 int /*<<< orphan*/  hv_set_drvdata (struct hv_device*,struct hv_pcibus_device*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_alloc_fwnode (struct hv_pcibus_device*) ; 
 int /*<<< orphan*/  irq_domain_free_fwnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_ring_size ; 
 int /*<<< orphan*/  prepopulate_bars (struct hv_pcibus_device*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_close (int /*<<< orphan*/ ) ; 
 int vmbus_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hv_pcibus_device*) ; 

__attribute__((used)) static int hv_pci_probe(struct hv_device *hdev,
			const struct hv_vmbus_device_id *dev_id)
{
	struct hv_pcibus_device *hbus;
	int ret;

	/*
	 * hv_pcibus_device contains the hypercall arguments for retargeting in
	 * hv_irq_unmask(). Those must not cross a page boundary.
	 */
	BUILD_BUG_ON(sizeof(*hbus) > PAGE_SIZE);

	hbus = (struct hv_pcibus_device *)get_zeroed_page(GFP_KERNEL);
	if (!hbus)
		return -ENOMEM;
	hbus->state = hv_pcibus_init;

	/*
	 * The PCI bus "domain" is what is called "segment" in ACPI and
	 * other specs.  Pull it from the instance ID, to get something
	 * unique.  Bytes 8 and 9 are what is used in Windows guests, so
	 * do the same thing for consistency.  Note that, since this code
	 * only runs in a Hyper-V VM, Hyper-V can (and does) guarantee
	 * that (1) the only domain in use for something that looks like
	 * a physical PCI bus (which is actually emulated by the
	 * hypervisor) is domain 0 and (2) there will be no overlap
	 * between domains derived from these instance IDs in the same
	 * VM.
	 */
	hbus->sysdata.domain = hdev->dev_instance.b[9] |
			       hdev->dev_instance.b[8] << 8;

	hbus->hdev = hdev;
	refcount_set(&hbus->remove_lock, 1);
	INIT_LIST_HEAD(&hbus->children);
	INIT_LIST_HEAD(&hbus->dr_list);
	INIT_LIST_HEAD(&hbus->resources_for_children);
	spin_lock_init(&hbus->config_lock);
	spin_lock_init(&hbus->device_list_lock);
	spin_lock_init(&hbus->retarget_msi_interrupt_lock);
	init_completion(&hbus->remove_event);
	hbus->wq = alloc_ordered_workqueue("hv_pci_%x", 0,
					   hbus->sysdata.domain);
	if (!hbus->wq) {
		ret = -ENOMEM;
		goto free_bus;
	}

	ret = vmbus_open(hdev->channel, pci_ring_size, pci_ring_size, NULL, 0,
			 hv_pci_onchannelcallback, hbus);
	if (ret)
		goto destroy_wq;

	hv_set_drvdata(hdev, hbus);

	ret = hv_pci_protocol_negotiation(hdev);
	if (ret)
		goto close;

	ret = hv_allocate_config_window(hbus);
	if (ret)
		goto close;

	hbus->cfg_addr = ioremap(hbus->mem_config->start,
				 PCI_CONFIG_MMIO_LENGTH);
	if (!hbus->cfg_addr) {
		dev_err(&hdev->device,
			"Unable to map a virtual address for config space\n");
		ret = -ENOMEM;
		goto free_config;
	}

	hbus->sysdata.fwnode = irq_domain_alloc_fwnode(hbus);
	if (!hbus->sysdata.fwnode) {
		ret = -ENOMEM;
		goto unmap;
	}

	ret = hv_pcie_init_irq_domain(hbus);
	if (ret)
		goto free_fwnode;

	ret = hv_pci_query_relations(hdev);
	if (ret)
		goto free_irq_domain;

	ret = hv_pci_enter_d0(hdev);
	if (ret)
		goto free_irq_domain;

	ret = hv_pci_allocate_bridge_windows(hbus);
	if (ret)
		goto free_irq_domain;

	ret = hv_send_resources_allocated(hdev);
	if (ret)
		goto free_windows;

	prepopulate_bars(hbus);

	hbus->state = hv_pcibus_probed;

	ret = create_root_hv_pci_bus(hbus);
	if (ret)
		goto free_windows;

	return 0;

free_windows:
	hv_pci_free_bridge_windows(hbus);
free_irq_domain:
	irq_domain_remove(hbus->irq_domain);
free_fwnode:
	irq_domain_free_fwnode(hbus->sysdata.fwnode);
unmap:
	iounmap(hbus->cfg_addr);
free_config:
	hv_free_config_window(hbus);
close:
	vmbus_close(hdev->channel);
destroy_wq:
	destroy_workqueue(hbus->wq);
free_bus:
	free_page((unsigned long)hbus);
	return ret;
}