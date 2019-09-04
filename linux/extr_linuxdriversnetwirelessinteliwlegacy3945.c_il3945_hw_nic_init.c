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
struct il_rx_queue {int write; int /*<<< orphan*/  bd; } ;
struct il_priv {int /*<<< orphan*/  status; int /*<<< orphan*/  lock; struct il_rx_queue rxq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FH39_RCSR_WPTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 int /*<<< orphan*/  S_INIT ; 
 int /*<<< orphan*/  il3945_apm_init (struct il_priv*) ; 
 int /*<<< orphan*/  il3945_nic_config (struct il_priv*) ; 
 int /*<<< orphan*/  il3945_rx_init (struct il_priv*,struct il_rx_queue*) ; 
 int /*<<< orphan*/  il3945_rx_queue_reset (struct il_priv*,struct il_rx_queue*) ; 
 int /*<<< orphan*/  il3945_rx_replenish (struct il_priv*) ; 
 int /*<<< orphan*/  il3945_set_pwr_vmain (struct il_priv*) ; 
 int il3945_txq_ctx_reset (struct il_priv*) ; 
 int il_rx_queue_alloc (struct il_priv*) ; 
 int /*<<< orphan*/  il_wr (struct il_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
il3945_hw_nic_init(struct il_priv *il)
{
	int rc;
	unsigned long flags;
	struct il_rx_queue *rxq = &il->rxq;

	spin_lock_irqsave(&il->lock, flags);
	il3945_apm_init(il);
	spin_unlock_irqrestore(&il->lock, flags);

	il3945_set_pwr_vmain(il);
	il3945_nic_config(il);

	/* Allocate the RX queue, or reset if it is already allocated */
	if (!rxq->bd) {
		rc = il_rx_queue_alloc(il);
		if (rc) {
			IL_ERR("Unable to initialize Rx queue\n");
			return -ENOMEM;
		}
	} else
		il3945_rx_queue_reset(il, rxq);

	il3945_rx_replenish(il);

	il3945_rx_init(il, rxq);

	/* Look at using this instead:
	   rxq->need_update = 1;
	   il_rx_queue_update_write_ptr(il, rxq);
	 */

	il_wr(il, FH39_RCSR_WPTR(0), rxq->write & ~7);

	rc = il3945_txq_ctx_reset(il);
	if (rc)
		return rc;

	set_bit(S_INIT, &il->status);

	return 0;
}