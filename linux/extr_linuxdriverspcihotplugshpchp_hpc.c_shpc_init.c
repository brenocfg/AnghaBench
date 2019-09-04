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
typedef  int u8 ;
typedef  int u32 ;
struct pci_dev {int irq; int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;
struct controller {int mmio_base; int mmio_size; int cap_offset; int creg; int slot_device_offset; int num_slots; int first_slot; int slot_num_inc; struct pci_dev* pci_dev; int /*<<< orphan*/  poll_timer; int /*<<< orphan*/ * hpc_ops; int /*<<< orphan*/  queue; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  crit_sect; } ;

/* Variables and functions */
 int ARBITER_SERR_MASK ; 
 int BUTTON_PRESS_INTR_MASK ; 
 int COMMAND_INTR_MASK ; 
 int CON_PFAULT_INTR_MASK ; 
 int CON_PFAULT_SERR_MASK ; 
 int FIRST_DEV_NUM ; 
 int GLOBAL_INTR_MASK ; 
 int GLOBAL_SERR_MASK ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int ISO_PFAULT_INTR_MASK ; 
 int MRL_CHANGE_INTR_MASK ; 
 int MRL_CHANGE_SERR_MASK ; 
 int /*<<< orphan*/  MY_NAME ; 
 int /*<<< orphan*/  PCI_CAP_ID_SHPC ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_AMD_GOLAM_7450 ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_AMD ; 
 int PRSNT_CHANGE_INTR_MASK ; 
 int PSN ; 
 int /*<<< orphan*/  SERR_INTR_ENABLE ; 
 int SERR_INTR_RSVDZ_MASK ; 
 int /*<<< orphan*/  SLOT_CONFIG ; 
 int SLOT_NUM ; 
 int /*<<< orphan*/  SLOT_REG (int) ; 
 int SLOT_REG_RSVDZ_MASK ; 
 int UPDOWN ; 
 int /*<<< orphan*/  ctrl_dbg (struct controller*,char*,...) ; 
 int /*<<< orphan*/  ctrl_err (struct controller*,char*,...) ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,...) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  int_poll_timeout ; 
 int ioremap (int,int) ; 
 int /*<<< orphan*/  iounmap (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int pci_enable_msi (struct pci_dev*) ; 
 int pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  release_mem_region (int,int) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  request_mem_region (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shpc_get_cur_bus_speed (struct controller*) ; 
 int /*<<< orphan*/  shpc_get_max_bus_speed (struct controller*) ; 
 int shpc_indirect_read (struct controller*,int,int*) ; 
 int /*<<< orphan*/  shpc_isr ; 
 int shpc_readl (struct controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shpc_writel (struct controller*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  shpchp_hpc_ops ; 
 scalar_t__ shpchp_poll_mode ; 
 int /*<<< orphan*/  start_int_poll_timer (struct controller*,int) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int shpc_init(struct controller *ctrl, struct pci_dev *pdev)
{
	int rc = -1, num_slots = 0;
	u8 hp_slot;
	u32 shpc_base_offset;
	u32 tempdword, slot_reg, slot_config;
	u8 i;

	ctrl->pci_dev = pdev;  /* pci_dev of the P2P bridge */
	ctrl_dbg(ctrl, "Hotplug Controller:\n");

	if (pdev->vendor == PCI_VENDOR_ID_AMD &&
	    pdev->device == PCI_DEVICE_ID_AMD_GOLAM_7450) {
		/* amd shpc driver doesn't use Base Offset; assume 0 */
		ctrl->mmio_base = pci_resource_start(pdev, 0);
		ctrl->mmio_size = pci_resource_len(pdev, 0);
	} else {
		ctrl->cap_offset = pci_find_capability(pdev, PCI_CAP_ID_SHPC);
		if (!ctrl->cap_offset) {
			ctrl_err(ctrl, "Cannot find PCI capability\n");
			goto abort;
		}
		ctrl_dbg(ctrl, " cap_offset = %x\n", ctrl->cap_offset);

		rc = shpc_indirect_read(ctrl, 0, &shpc_base_offset);
		if (rc) {
			ctrl_err(ctrl, "Cannot read base_offset\n");
			goto abort;
		}

		rc = shpc_indirect_read(ctrl, 3, &tempdword);
		if (rc) {
			ctrl_err(ctrl, "Cannot read slot config\n");
			goto abort;
		}
		num_slots = tempdword & SLOT_NUM;
		ctrl_dbg(ctrl, " num_slots (indirect) %x\n", num_slots);

		for (i = 0; i < 9 + num_slots; i++) {
			rc = shpc_indirect_read(ctrl, i, &tempdword);
			if (rc) {
				ctrl_err(ctrl, "Cannot read creg (index = %d)\n",
					 i);
				goto abort;
			}
			ctrl_dbg(ctrl, " offset %d: value %x\n", i, tempdword);
		}

		ctrl->mmio_base =
			pci_resource_start(pdev, 0) + shpc_base_offset;
		ctrl->mmio_size = 0x24 + 0x4 * num_slots;
	}

	ctrl_info(ctrl, "HPC vendor_id %x device_id %x ss_vid %x ss_did %x\n",
		  pdev->vendor, pdev->device, pdev->subsystem_vendor,
		  pdev->subsystem_device);

	rc = pci_enable_device(pdev);
	if (rc) {
		ctrl_err(ctrl, "pci_enable_device failed\n");
		goto abort;
	}

	if (!request_mem_region(ctrl->mmio_base, ctrl->mmio_size, MY_NAME)) {
		ctrl_err(ctrl, "Cannot reserve MMIO region\n");
		rc = -1;
		goto abort;
	}

	ctrl->creg = ioremap(ctrl->mmio_base, ctrl->mmio_size);
	if (!ctrl->creg) {
		ctrl_err(ctrl, "Cannot remap MMIO region %lx @ %lx\n",
			 ctrl->mmio_size, ctrl->mmio_base);
		release_mem_region(ctrl->mmio_base, ctrl->mmio_size);
		rc = -1;
		goto abort;
	}
	ctrl_dbg(ctrl, "ctrl->creg %p\n", ctrl->creg);

	mutex_init(&ctrl->crit_sect);
	mutex_init(&ctrl->cmd_lock);

	/* Setup wait queue */
	init_waitqueue_head(&ctrl->queue);

	ctrl->hpc_ops = &shpchp_hpc_ops;

	/* Return PCI Controller Info */
	slot_config = shpc_readl(ctrl, SLOT_CONFIG);
	ctrl->slot_device_offset = (slot_config & FIRST_DEV_NUM) >> 8;
	ctrl->num_slots = slot_config & SLOT_NUM;
	ctrl->first_slot = (slot_config & PSN) >> 16;
	ctrl->slot_num_inc = ((slot_config & UPDOWN) >> 29) ? 1 : -1;

	/* Mask Global Interrupt Mask & Command Complete Interrupt Mask */
	tempdword = shpc_readl(ctrl, SERR_INTR_ENABLE);
	ctrl_dbg(ctrl, "SERR_INTR_ENABLE = %x\n", tempdword);
	tempdword |= (GLOBAL_INTR_MASK  | GLOBAL_SERR_MASK |
		      COMMAND_INTR_MASK | ARBITER_SERR_MASK);
	tempdword &= ~SERR_INTR_RSVDZ_MASK;
	shpc_writel(ctrl, SERR_INTR_ENABLE, tempdword);
	tempdword = shpc_readl(ctrl, SERR_INTR_ENABLE);
	ctrl_dbg(ctrl, "SERR_INTR_ENABLE = %x\n", tempdword);

	/* Mask the MRL sensor SERR Mask of individual slot in
	 * Slot SERR-INT Mask & clear all the existing event if any
	 */
	for (hp_slot = 0; hp_slot < ctrl->num_slots; hp_slot++) {
		slot_reg = shpc_readl(ctrl, SLOT_REG(hp_slot));
		ctrl_dbg(ctrl, "Default Logical Slot Register %d value %x\n",
			 hp_slot, slot_reg);
		slot_reg |= (PRSNT_CHANGE_INTR_MASK | ISO_PFAULT_INTR_MASK |
			     BUTTON_PRESS_INTR_MASK | MRL_CHANGE_INTR_MASK |
			     CON_PFAULT_INTR_MASK   | MRL_CHANGE_SERR_MASK |
			     CON_PFAULT_SERR_MASK);
		slot_reg &= ~SLOT_REG_RSVDZ_MASK;
		shpc_writel(ctrl, SLOT_REG(hp_slot), slot_reg);
	}

	if (shpchp_poll_mode) {
		/* Install interrupt polling timer. Start with 10 sec delay */
		timer_setup(&ctrl->poll_timer, int_poll_timeout, 0);
		start_int_poll_timer(ctrl, 10);
	} else {
		/* Installs the interrupt handler */
		rc = pci_enable_msi(pdev);
		if (rc) {
			ctrl_info(ctrl, "Can't get msi for the hotplug controller\n");
			ctrl_info(ctrl, "Use INTx for the hotplug controller\n");
		} else {
			pci_set_master(pdev);
		}

		rc = request_irq(ctrl->pci_dev->irq, shpc_isr, IRQF_SHARED,
				 MY_NAME, (void *)ctrl);
		ctrl_dbg(ctrl, "request_irq %d (returns %d)\n",
			 ctrl->pci_dev->irq, rc);
		if (rc) {
			ctrl_err(ctrl, "Can't get irq %d for the hotplug controller\n",
				 ctrl->pci_dev->irq);
			goto abort_iounmap;
		}
	}
	ctrl_dbg(ctrl, "HPC at %s irq=%x\n", pci_name(pdev), pdev->irq);

	shpc_get_max_bus_speed(ctrl);
	shpc_get_cur_bus_speed(ctrl);

	/*
	 * Unmask all event interrupts of all slots
	 */
	for (hp_slot = 0; hp_slot < ctrl->num_slots; hp_slot++) {
		slot_reg = shpc_readl(ctrl, SLOT_REG(hp_slot));
		ctrl_dbg(ctrl, "Default Logical Slot Register %d value %x\n",
			 hp_slot, slot_reg);
		slot_reg &= ~(PRSNT_CHANGE_INTR_MASK | ISO_PFAULT_INTR_MASK |
			      BUTTON_PRESS_INTR_MASK | MRL_CHANGE_INTR_MASK |
			      CON_PFAULT_INTR_MASK | SLOT_REG_RSVDZ_MASK);
		shpc_writel(ctrl, SLOT_REG(hp_slot), slot_reg);
	}
	if (!shpchp_poll_mode) {
		/* Unmask all general input interrupts and SERR */
		tempdword = shpc_readl(ctrl, SERR_INTR_ENABLE);
		tempdword &= ~(GLOBAL_INTR_MASK | COMMAND_INTR_MASK |
			       SERR_INTR_RSVDZ_MASK);
		shpc_writel(ctrl, SERR_INTR_ENABLE, tempdword);
		tempdword = shpc_readl(ctrl, SERR_INTR_ENABLE);
		ctrl_dbg(ctrl, "SERR_INTR_ENABLE = %x\n", tempdword);
	}

	return 0;

	/* We end up here for the many possible ways to fail this API.  */
abort_iounmap:
	iounmap(ctrl->creg);
abort:
	return rc;
}