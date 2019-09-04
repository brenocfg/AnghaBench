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
typedef  int uint32_t ;
struct ioc4_soft {TYPE_1__* is_intr_type; } ;
struct ioc4_intr_info {int sd_bits; int /*<<< orphan*/  sd_info; int /*<<< orphan*/  (* sd_intr ) (int /*<<< orphan*/ ,int) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct ioc4_intr_info* is_intr_info; int /*<<< orphan*/  is_num_intrs; } ;

/* Variables and functions */
 int IOC4_NUM_INTR_TYPES ; 
 int /*<<< orphan*/  IOC4_W_IEC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int pending_intrs (struct ioc4_soft*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_ireg (struct ioc4_soft*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t ioc4_intr(int irq, void *arg)
{
	struct ioc4_soft *soft;
	uint32_t this_ir, this_mir;
	int xx, num_intrs = 0;
	int intr_type;
	int handled = 0;
	struct ioc4_intr_info *intr_info;

	soft = arg;
	for (intr_type = 0; intr_type < IOC4_NUM_INTR_TYPES; intr_type++) {
		num_intrs = (int)atomic_read(
				&soft->is_intr_type[intr_type].is_num_intrs);

		this_mir = this_ir = pending_intrs(soft, intr_type);

		/* Farm out the interrupt to the various drivers depending on
		 * which interrupt bits are set.
		 */
		for (xx = 0; xx < num_intrs; xx++) {
			intr_info = &soft->is_intr_type[intr_type].is_intr_info[xx];
			this_mir = this_ir & intr_info->sd_bits;
			if (this_mir) {
				/* Disable owned interrupts, call handler */
				handled++;
				write_ireg(soft, intr_info->sd_bits, IOC4_W_IEC,
								intr_type);
				intr_info->sd_intr(intr_info->sd_info, this_mir);
				this_ir &= ~this_mir;
			}
		}
	}
#ifdef DEBUG_INTERRUPTS
	{
		struct ioc4_misc_regs __iomem *mem = soft->is_ioc4_misc_addr;
		unsigned long flag;

		spin_lock_irqsave(&soft->is_ir_lock, flag);
		printk ("%s : %d : mem 0x%p sio_ir 0x%x sio_ies 0x%x "
				"other_ir 0x%x other_ies 0x%x mask 0x%x\n",
		     __func__, __LINE__,
		     (void *)mem, readl(&mem->sio_ir.raw),
		     readl(&mem->sio_ies.raw),
		     readl(&mem->other_ir.raw),
		     readl(&mem->other_ies.raw),
		     IOC4_OTHER_IR_ATA_INT | IOC4_OTHER_IR_ATA_MEMERR);
		spin_unlock_irqrestore(&soft->is_ir_lock, flag);
	}
#endif
	return handled ? IRQ_HANDLED : IRQ_NONE;
}