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
typedef  int u32 ;
struct megasas_irq_context {int /*<<< orphan*/  MSIxIndex; struct megasas_instance* instance; } ;
struct megasas_instance {scalar_t__ unload; int /*<<< orphan*/  work_init; TYPE_3__* host; TYPE_2__* pdev; int /*<<< orphan*/  crash_init; scalar_t__ crash_dump_app_support; scalar_t__ crash_dump_drv_support; int /*<<< orphan*/  reg_set; TYPE_1__* instancet; int /*<<< orphan*/  reset_flags; int /*<<< orphan*/  msix_vectors; scalar_t__ mask_interrupts; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int /*<<< orphan*/  host_no; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int (* clear_intr ) (int /*<<< orphan*/ ) ;int (* read_fw_status_reg ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  MEGASAS_FUSION_IN_RESET ; 
 int MFI_STATE_DMADONE ; 
 int MFI_STATE_FAULT ; 
 int MFI_STATE_MASK ; 
 int /*<<< orphan*/  complete_cmd_fusion (struct megasas_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ) ; 
 int stub3 (int /*<<< orphan*/ ) ; 
 int stub4 (int /*<<< orphan*/ ) ; 
 int stub5 (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

irqreturn_t megasas_isr_fusion(int irq, void *devp)
{
	struct megasas_irq_context *irq_context = devp;
	struct megasas_instance *instance = irq_context->instance;
	u32 mfiStatus, fw_state, dma_state;

	if (instance->mask_interrupts)
		return IRQ_NONE;

	if (!instance->msix_vectors) {
		mfiStatus = instance->instancet->clear_intr(instance->reg_set);
		if (!mfiStatus)
			return IRQ_NONE;
	}

	/* If we are resetting, bail */
	if (test_bit(MEGASAS_FUSION_IN_RESET, &instance->reset_flags)) {
		instance->instancet->clear_intr(instance->reg_set);
		return IRQ_HANDLED;
	}

	if (!complete_cmd_fusion(instance, irq_context->MSIxIndex)) {
		instance->instancet->clear_intr(instance->reg_set);
		/* If we didn't complete any commands, check for FW fault */
		fw_state = instance->instancet->read_fw_status_reg(
			instance->reg_set) & MFI_STATE_MASK;
		dma_state = instance->instancet->read_fw_status_reg
			(instance->reg_set) & MFI_STATE_DMADONE;
		if (instance->crash_dump_drv_support &&
			instance->crash_dump_app_support) {
			/* Start collecting crash, if DMA bit is done */
			if ((fw_state == MFI_STATE_FAULT) && dma_state)
				schedule_work(&instance->crash_init);
			else if (fw_state == MFI_STATE_FAULT) {
				if (instance->unload == 0)
					schedule_work(&instance->work_init);
			}
		} else if (fw_state == MFI_STATE_FAULT) {
			dev_warn(&instance->pdev->dev, "Iop2SysDoorbellInt"
			       "for scsi%d\n", instance->host->host_no);
			if (instance->unload == 0)
				schedule_work(&instance->work_init);
		}
	}

	return IRQ_HANDLED;
}