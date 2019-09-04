#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct megasas_instance {TYPE_2__* pdev; TYPE_3__* reg_set; TYPE_1__* instancet; int /*<<< orphan*/  adapter_type; } ;
struct TYPE_7__ {int /*<<< orphan*/  inbound_doorbell; int /*<<< orphan*/  doorbell; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  device; } ;
struct TYPE_5__ {int (* read_fw_status_reg ) (TYPE_3__*) ;int /*<<< orphan*/  (* disable_intr ) (struct megasas_instance*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int MEGASAS_RESET_WAIT_TIME ; 
 int MFI_INIT_CLEAR_HANDSHAKE ; 
 int MFI_INIT_HOTPLUG ; 
 int MFI_RESET_FLAGS ; 
 int /*<<< orphan*/  MFI_SERIES ; 
#define  MFI_STATE_BB_INIT 137 
#define  MFI_STATE_BOOT_MESSAGE_PENDING 136 
#define  MFI_STATE_DEVICE_SCAN 135 
#define  MFI_STATE_FAULT 134 
#define  MFI_STATE_FLUSH_CACHE 133 
#define  MFI_STATE_FW_INIT 132 
#define  MFI_STATE_FW_INIT_2 131 
 int MFI_STATE_MASK ; 
#define  MFI_STATE_OPERATIONAL 130 
 int MFI_STATE_READY ; 
#define  MFI_STATE_UNDEFINED 129 
#define  MFI_STATE_WAIT_HANDSHAKE 128 
 int /*<<< orphan*/  PCI_DEVICE_ID_LSI_SAS0071SKINNY ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_LSI_SAS0073SKINNY ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (struct megasas_instance*) ; 
 int stub3 (TYPE_3__*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

int
megasas_transition_to_ready(struct megasas_instance *instance, int ocr)
{
	int i;
	u8 max_wait;
	u32 fw_state;
	u32 cur_state;
	u32 abs_state, curr_abs_state;

	abs_state = instance->instancet->read_fw_status_reg(instance->reg_set);
	fw_state = abs_state & MFI_STATE_MASK;

	if (fw_state != MFI_STATE_READY)
		dev_info(&instance->pdev->dev, "Waiting for FW to come to ready"
		       " state\n");

	while (fw_state != MFI_STATE_READY) {

		switch (fw_state) {

		case MFI_STATE_FAULT:
			dev_printk(KERN_DEBUG, &instance->pdev->dev, "FW in FAULT state!!\n");
			if (ocr) {
				max_wait = MEGASAS_RESET_WAIT_TIME;
				cur_state = MFI_STATE_FAULT;
				break;
			} else
				return -ENODEV;

		case MFI_STATE_WAIT_HANDSHAKE:
			/*
			 * Set the CLR bit in inbound doorbell
			 */
			if ((instance->pdev->device ==
				PCI_DEVICE_ID_LSI_SAS0073SKINNY) ||
				(instance->pdev->device ==
				 PCI_DEVICE_ID_LSI_SAS0071SKINNY) ||
				(instance->adapter_type != MFI_SERIES))
				writel(
				  MFI_INIT_CLEAR_HANDSHAKE|MFI_INIT_HOTPLUG,
				  &instance->reg_set->doorbell);
			else
				writel(
				    MFI_INIT_CLEAR_HANDSHAKE|MFI_INIT_HOTPLUG,
					&instance->reg_set->inbound_doorbell);

			max_wait = MEGASAS_RESET_WAIT_TIME;
			cur_state = MFI_STATE_WAIT_HANDSHAKE;
			break;

		case MFI_STATE_BOOT_MESSAGE_PENDING:
			if ((instance->pdev->device ==
			     PCI_DEVICE_ID_LSI_SAS0073SKINNY) ||
				(instance->pdev->device ==
				 PCI_DEVICE_ID_LSI_SAS0071SKINNY) ||
				(instance->adapter_type != MFI_SERIES))
				writel(MFI_INIT_HOTPLUG,
				       &instance->reg_set->doorbell);
			else
				writel(MFI_INIT_HOTPLUG,
					&instance->reg_set->inbound_doorbell);

			max_wait = MEGASAS_RESET_WAIT_TIME;
			cur_state = MFI_STATE_BOOT_MESSAGE_PENDING;
			break;

		case MFI_STATE_OPERATIONAL:
			/*
			 * Bring it to READY state; assuming max wait 10 secs
			 */
			instance->instancet->disable_intr(instance);
			if ((instance->pdev->device ==
				PCI_DEVICE_ID_LSI_SAS0073SKINNY) ||
				(instance->pdev->device ==
				PCI_DEVICE_ID_LSI_SAS0071SKINNY)  ||
				(instance->adapter_type != MFI_SERIES)) {
				writel(MFI_RESET_FLAGS,
					&instance->reg_set->doorbell);

				if (instance->adapter_type != MFI_SERIES) {
					for (i = 0; i < (10 * 1000); i += 20) {
						if (readl(
							    &instance->
							    reg_set->
							    doorbell) & 1)
							msleep(20);
						else
							break;
					}
				}
			} else
				writel(MFI_RESET_FLAGS,
					&instance->reg_set->inbound_doorbell);

			max_wait = MEGASAS_RESET_WAIT_TIME;
			cur_state = MFI_STATE_OPERATIONAL;
			break;

		case MFI_STATE_UNDEFINED:
			/*
			 * This state should not last for more than 2 seconds
			 */
			max_wait = MEGASAS_RESET_WAIT_TIME;
			cur_state = MFI_STATE_UNDEFINED;
			break;

		case MFI_STATE_BB_INIT:
			max_wait = MEGASAS_RESET_WAIT_TIME;
			cur_state = MFI_STATE_BB_INIT;
			break;

		case MFI_STATE_FW_INIT:
			max_wait = MEGASAS_RESET_WAIT_TIME;
			cur_state = MFI_STATE_FW_INIT;
			break;

		case MFI_STATE_FW_INIT_2:
			max_wait = MEGASAS_RESET_WAIT_TIME;
			cur_state = MFI_STATE_FW_INIT_2;
			break;

		case MFI_STATE_DEVICE_SCAN:
			max_wait = MEGASAS_RESET_WAIT_TIME;
			cur_state = MFI_STATE_DEVICE_SCAN;
			break;

		case MFI_STATE_FLUSH_CACHE:
			max_wait = MEGASAS_RESET_WAIT_TIME;
			cur_state = MFI_STATE_FLUSH_CACHE;
			break;

		default:
			dev_printk(KERN_DEBUG, &instance->pdev->dev, "Unknown state 0x%x\n",
			       fw_state);
			return -ENODEV;
		}

		/*
		 * The cur_state should not last for more than max_wait secs
		 */
		for (i = 0; i < (max_wait * 1000); i++) {
			curr_abs_state = instance->instancet->
				read_fw_status_reg(instance->reg_set);

			if (abs_state == curr_abs_state) {
				msleep(1);
			} else
				break;
		}

		/*
		 * Return error if fw_state hasn't changed after max_wait
		 */
		if (curr_abs_state == abs_state) {
			dev_printk(KERN_DEBUG, &instance->pdev->dev, "FW state [%d] hasn't changed "
			       "in %d secs\n", fw_state, max_wait);
			return -ENODEV;
		}

		abs_state = curr_abs_state;
		fw_state = curr_abs_state & MFI_STATE_MASK;
	}
	dev_info(&instance->pdev->dev, "FW now in Ready state\n");

	return 0;
}