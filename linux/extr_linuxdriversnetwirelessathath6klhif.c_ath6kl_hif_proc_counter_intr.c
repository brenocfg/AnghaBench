#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {int cntr_int_status_en; } ;
struct TYPE_3__ {int counter_int_status; } ;
struct ath6kl_device {TYPE_2__ irq_en_reg; TYPE_1__ irq_proc_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_IRQ ; 
 int ATH6KL_TARGET_DEBUG_INTR_MASK ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int ath6kl_hif_proc_dbg_intr (struct ath6kl_device*) ; 

__attribute__((used)) static int ath6kl_hif_proc_counter_intr(struct ath6kl_device *dev)
{
	u8 counter_int_status;

	ath6kl_dbg(ATH6KL_DBG_IRQ, "counter interrupt\n");

	counter_int_status = dev->irq_proc_reg.counter_int_status &
			     dev->irq_en_reg.cntr_int_status_en;

	ath6kl_dbg(ATH6KL_DBG_IRQ,
		   "valid interrupt source(s) in COUNTER_INT_STATUS: 0x%x\n",
		counter_int_status);

	/*
	 * NOTE: other modules like GMBOX may use the counter interrupt for
	 * credit flow control on other counters, we only need to check for
	 * the debug assertion counter interrupt.
	 */
	if (counter_int_status & ATH6KL_TARGET_DEBUG_INTR_MASK)
		return ath6kl_hif_proc_dbg_intr(dev);

	return 0;
}