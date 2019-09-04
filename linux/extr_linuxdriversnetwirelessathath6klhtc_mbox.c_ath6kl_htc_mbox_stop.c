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
struct htc_target {int /*<<< orphan*/  dev; int /*<<< orphan*/  htc_lock; int /*<<< orphan*/  htc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HTC_OP_STATE_STOPPING ; 
 int /*<<< orphan*/  ath6kl_hif_mask_intrs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_htc_flush_txep_all (struct htc_target*) ; 
 int /*<<< orphan*/  ath6kl_htc_mbox_flush_rx_buf (struct htc_target*) ; 
 int /*<<< orphan*/  ath6kl_htc_reset (struct htc_target*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath6kl_htc_mbox_stop(struct htc_target *target)
{
	spin_lock_bh(&target->htc_lock);
	target->htc_flags |= HTC_OP_STATE_STOPPING;
	spin_unlock_bh(&target->htc_lock);

	/*
	 * Masking interrupts is a synchronous operation, when this
	 * function returns all pending HIF I/O has completed, we can
	 * safely flush the queues.
	 */
	ath6kl_hif_mask_intrs(target->dev);

	ath6kl_htc_flush_txep_all(target);

	ath6kl_htc_mbox_flush_rx_buf(target);

	ath6kl_htc_reset(target);
}