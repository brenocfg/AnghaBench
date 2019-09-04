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
typedef  int u32 ;
struct il_rx_queue {scalar_t__ need_update; int write_actual; int write; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int rx_wrt_ptr_reg; } ;
struct il_priv {int /*<<< orphan*/  status; TYPE_1__ hw_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 int /*<<< orphan*/  CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ ; 
 int /*<<< orphan*/  CSR_UCODE_DRV_GP1 ; 
 int CSR_UCODE_DRV_GP1_BIT_MAC_SLEEP ; 
 int /*<<< orphan*/  D_INFO (char*,int) ; 
 int /*<<< orphan*/  S_POWER_PMI ; 
 int _il_rd (struct il_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_set_bit (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_wr (struct il_priv*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
il_rx_queue_update_write_ptr(struct il_priv *il, struct il_rx_queue *q)
{
	unsigned long flags;
	u32 rx_wrt_ptr_reg = il->hw_params.rx_wrt_ptr_reg;
	u32 reg;

	spin_lock_irqsave(&q->lock, flags);

	if (q->need_update == 0)
		goto exit_unlock;

	/* If power-saving is in use, make sure device is awake */
	if (test_bit(S_POWER_PMI, &il->status)) {
		reg = _il_rd(il, CSR_UCODE_DRV_GP1);

		if (reg & CSR_UCODE_DRV_GP1_BIT_MAC_SLEEP) {
			D_INFO("Rx queue requesting wakeup," " GP1 = 0x%x\n",
			       reg);
			il_set_bit(il, CSR_GP_CNTRL,
				   CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);
			goto exit_unlock;
		}

		q->write_actual = (q->write & ~0x7);
		il_wr(il, rx_wrt_ptr_reg, q->write_actual);

		/* Else device is assumed to be awake */
	} else {
		/* Device expects a multiple of 8 */
		q->write_actual = (q->write & ~0x7);
		il_wr(il, rx_wrt_ptr_reg, q->write_actual);
	}

	q->need_update = 0;

exit_unlock:
	spin_unlock_irqrestore(&q->lock, flags);
}