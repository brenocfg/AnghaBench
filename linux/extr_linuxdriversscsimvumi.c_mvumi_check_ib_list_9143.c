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
struct mvumi_hw_regs {unsigned int cl_slot_num_mask; unsigned int cl_pointer_toggle; int /*<<< orphan*/  inb_read_pointer; } ;
struct mvumi_hba {unsigned int ib_cur_slot; scalar_t__ max_io; int /*<<< orphan*/  fw_outstanding; TYPE_1__* pdev; struct mvumi_hw_regs* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 unsigned int ioread32 (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int mvumi_check_ib_list_9143(struct mvumi_hba *mhba)
{
	unsigned int ib_rp_reg;
	struct mvumi_hw_regs *regs = mhba->regs;

	ib_rp_reg = ioread32(mhba->regs->inb_read_pointer);

	if (unlikely(((ib_rp_reg & regs->cl_slot_num_mask) ==
			(mhba->ib_cur_slot & regs->cl_slot_num_mask)) &&
			((ib_rp_reg & regs->cl_pointer_toggle)
			 != (mhba->ib_cur_slot & regs->cl_pointer_toggle)))) {
		dev_warn(&mhba->pdev->dev, "no free slot to use.\n");
		return 0;
	}
	if (atomic_read(&mhba->fw_outstanding) >= mhba->max_io) {
		dev_warn(&mhba->pdev->dev, "firmware io overflow.\n");
		return 0;
	} else {
		return mhba->max_io - atomic_read(&mhba->fw_outstanding);
	}
}