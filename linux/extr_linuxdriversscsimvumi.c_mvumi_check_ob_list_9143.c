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
struct mvumi_hw_regs {unsigned int cl_slot_num_mask; unsigned int cl_pointer_toggle; int /*<<< orphan*/  outb_copy_pointer; } ;
struct mvumi_hba {unsigned int ob_cur_slot; scalar_t__ list_num_io; struct mvumi_hw_regs* regs; int /*<<< orphan*/  ob_shadow; } ;

/* Variables and functions */
 unsigned int ioread32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvumi_check_ob_list_9143(struct mvumi_hba *mhba,
			unsigned int *cur_obf, unsigned int *assign_obf_end)
{
	unsigned int ob_write, ob_write_shadow;
	struct mvumi_hw_regs *regs = mhba->regs;

	do {
		ob_write = ioread32(regs->outb_copy_pointer);
		ob_write_shadow = ioread32(mhba->ob_shadow);
	} while ((ob_write & regs->cl_slot_num_mask) != ob_write_shadow);

	*cur_obf = mhba->ob_cur_slot & mhba->regs->cl_slot_num_mask;
	*assign_obf_end = ob_write & mhba->regs->cl_slot_num_mask;

	if ((ob_write & regs->cl_pointer_toggle) !=
			(mhba->ob_cur_slot & regs->cl_pointer_toggle)) {
		*assign_obf_end += mhba->list_num_io;
	}
	return 0;
}