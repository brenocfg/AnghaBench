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
struct TYPE_4__ {int cpu_int_status; } ;
struct TYPE_3__ {int cpu_int_status_en; } ;
struct ath6kl_device {int /*<<< orphan*/  ar; TYPE_2__ irq_proc_reg; TYPE_1__ irq_en_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_IRQ ; 
 int /*<<< orphan*/  CPU_INT_STATUS_ADDRESS ; 
 int EIO ; 
 int /*<<< orphan*/  HIF_WR_SYNC_BYTE_FIX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int hif_read_write_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_hif_proc_cpu_intr(struct ath6kl_device *dev)
{
	int status;
	u8 cpu_int_status;
	u8 reg_buf[4];

	ath6kl_dbg(ATH6KL_DBG_IRQ, "cpu interrupt\n");

	cpu_int_status = dev->irq_proc_reg.cpu_int_status &
			 dev->irq_en_reg.cpu_int_status_en;
	if (!cpu_int_status) {
		WARN_ON(1);
		return -EIO;
	}

	ath6kl_dbg(ATH6KL_DBG_IRQ,
		   "valid interrupt source(s) in CPU_INT_STATUS: 0x%x\n",
		cpu_int_status);

	/* Clear the interrupt */
	dev->irq_proc_reg.cpu_int_status &= ~cpu_int_status;

	/*
	 * Set up the register transfer buffer to hit the register 4 times ,
	 * this is done to make the access 4-byte aligned to mitigate issues
	 * with host bus interconnects that restrict bus transfer lengths to
	 * be a multiple of 4-bytes.
	 */

	/* set W1C value to clear the interrupt, this hits the register first */
	reg_buf[0] = cpu_int_status;
	/* the remaining are set to zero which have no-effect  */
	reg_buf[1] = 0;
	reg_buf[2] = 0;
	reg_buf[3] = 0;

	status = hif_read_write_sync(dev->ar, CPU_INT_STATUS_ADDRESS,
				     reg_buf, 4, HIF_WR_SYNC_BYTE_FIX);

	WARN_ON(status);

	return status;
}