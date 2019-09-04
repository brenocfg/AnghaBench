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
struct mvumi_hw_regs {int int_comaout; int int_comaerr; int int_dl_cpu2pciea; int cl_pointer_toggle; int clic_irq; int clic_in_err; int clic_out_err; int cl_slot_num_mask; int int_drbl_int_mask; int int_mu; void* outb_isr_cause; void* outb_coal_cfg; void* outb_read_pointer; void* outb_copy_pointer; void* outb_copy_baseh; void* outb_copy_basel; void* inb_read_pointer; void* inb_write_pointer; void* inb_aval_count_baseh; void* inb_aval_count_basel; void* reset_enable; void* reset_request; void* arm_to_pciea_msg1; void* arm_to_pciea_msg0; void* pciea_to_arm_msg1; void* pciea_to_arm_msg0; void* arm_to_pciea_mask_reg; void* arm_to_pciea_drbl_reg; void* pciea_to_arm_drbl_reg; void* rstoutn_en_reg; void* enpointa_mask_reg; void* main_int_cause_reg; void* sys_soft_rst_reg; void* rstoutn_mask_reg; void* ctrl_sts_reg; } ;
struct mvumi_hba {struct mvumi_hw_regs* regs; void* mmio; void** base_addr; TYPE_1__* pdev; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  PCI_DEVICE_ID_MARVELL_MV9143 129 
#define  PCI_DEVICE_ID_MARVELL_MV9580 128 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvumi_cfg_hw_reg(struct mvumi_hba *mhba)
{
	void *base = NULL;
	struct mvumi_hw_regs *regs;

	switch (mhba->pdev->device) {
	case PCI_DEVICE_ID_MARVELL_MV9143:
		mhba->mmio = mhba->base_addr[0];
		base = mhba->mmio;
		if (!mhba->regs) {
			mhba->regs = kzalloc(sizeof(*regs), GFP_KERNEL);
			if (mhba->regs == NULL)
				return -ENOMEM;
		}
		regs = mhba->regs;

		/* For Arm */
		regs->ctrl_sts_reg          = base + 0x20104;
		regs->rstoutn_mask_reg      = base + 0x20108;
		regs->sys_soft_rst_reg      = base + 0x2010C;
		regs->main_int_cause_reg    = base + 0x20200;
		regs->enpointa_mask_reg     = base + 0x2020C;
		regs->rstoutn_en_reg        = base + 0xF1400;
		/* For Doorbell */
		regs->pciea_to_arm_drbl_reg = base + 0x20400;
		regs->arm_to_pciea_drbl_reg = base + 0x20408;
		regs->arm_to_pciea_mask_reg = base + 0x2040C;
		regs->pciea_to_arm_msg0     = base + 0x20430;
		regs->pciea_to_arm_msg1     = base + 0x20434;
		regs->arm_to_pciea_msg0     = base + 0x20438;
		regs->arm_to_pciea_msg1     = base + 0x2043C;

		/* For Message Unit */

		regs->inb_aval_count_basel  = base + 0x508;
		regs->inb_aval_count_baseh  = base + 0x50C;
		regs->inb_write_pointer     = base + 0x518;
		regs->inb_read_pointer      = base + 0x51C;
		regs->outb_coal_cfg         = base + 0x568;
		regs->outb_copy_basel       = base + 0x5B0;
		regs->outb_copy_baseh       = base + 0x5B4;
		regs->outb_copy_pointer     = base + 0x544;
		regs->outb_read_pointer     = base + 0x548;
		regs->outb_isr_cause        = base + 0x560;
		regs->outb_coal_cfg         = base + 0x568;
		/* Bit setting for HW */
		regs->int_comaout           = 1 << 8;
		regs->int_comaerr           = 1 << 6;
		regs->int_dl_cpu2pciea      = 1 << 1;
		regs->cl_pointer_toggle     = 1 << 12;
		regs->clic_irq              = 1 << 1;
		regs->clic_in_err           = 1 << 8;
		regs->clic_out_err          = 1 << 12;
		regs->cl_slot_num_mask      = 0xFFF;
		regs->int_drbl_int_mask     = 0x3FFFFFFF;
		regs->int_mu = regs->int_dl_cpu2pciea | regs->int_comaout |
							regs->int_comaerr;
		break;
	case PCI_DEVICE_ID_MARVELL_MV9580:
		mhba->mmio = mhba->base_addr[2];
		base = mhba->mmio;
		if (!mhba->regs) {
			mhba->regs = kzalloc(sizeof(*regs), GFP_KERNEL);
			if (mhba->regs == NULL)
				return -ENOMEM;
		}
		regs = mhba->regs;
		/* For Arm */
		regs->ctrl_sts_reg          = base + 0x20104;
		regs->rstoutn_mask_reg      = base + 0x1010C;
		regs->sys_soft_rst_reg      = base + 0x10108;
		regs->main_int_cause_reg    = base + 0x10200;
		regs->enpointa_mask_reg     = base + 0x1020C;
		regs->rstoutn_en_reg        = base + 0xF1400;

		/* For Doorbell */
		regs->pciea_to_arm_drbl_reg = base + 0x10460;
		regs->arm_to_pciea_drbl_reg = base + 0x10480;
		regs->arm_to_pciea_mask_reg = base + 0x10484;
		regs->pciea_to_arm_msg0     = base + 0x10400;
		regs->pciea_to_arm_msg1     = base + 0x10404;
		regs->arm_to_pciea_msg0     = base + 0x10420;
		regs->arm_to_pciea_msg1     = base + 0x10424;

		/* For reset*/
		regs->reset_request         = base + 0x10108;
		regs->reset_enable          = base + 0x1010c;

		/* For Message Unit */
		regs->inb_aval_count_basel  = base + 0x4008;
		regs->inb_aval_count_baseh  = base + 0x400C;
		regs->inb_write_pointer     = base + 0x4018;
		regs->inb_read_pointer      = base + 0x401C;
		regs->outb_copy_basel       = base + 0x4058;
		regs->outb_copy_baseh       = base + 0x405C;
		regs->outb_copy_pointer     = base + 0x406C;
		regs->outb_read_pointer     = base + 0x4070;
		regs->outb_coal_cfg         = base + 0x4080;
		regs->outb_isr_cause        = base + 0x4088;
		/* Bit setting for HW */
		regs->int_comaout           = 1 << 4;
		regs->int_dl_cpu2pciea      = 1 << 12;
		regs->int_comaerr           = 1 << 29;
		regs->cl_pointer_toggle     = 1 << 14;
		regs->cl_slot_num_mask      = 0x3FFF;
		regs->clic_irq              = 1 << 0;
		regs->clic_out_err          = 1 << 1;
		regs->int_drbl_int_mask     = 0x3FFFFFFF;
		regs->int_mu = regs->int_dl_cpu2pciea | regs->int_comaout;
		break;
	default:
		return -1;
		break;
	}

	return 0;
}