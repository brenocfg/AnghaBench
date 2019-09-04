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
struct htc_target {int tx_bndl_mask; int rx_bndl_enable; int tgt_cred_sz; int block_sz; void* max_rx_bndl_sz; void* max_tx_bndl_sz; void* max_xfer_szper_scatreq; void* msg_per_bndl_max; int /*<<< orphan*/  max_scat_entries; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  ar; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_BOOT ; 
 int /*<<< orphan*/  HIF_MBOX0_EXT_WIDTH ; 
 int /*<<< orphan*/  HTC_HOST_MAX_MSG_PER_BUNDLE ; 
 int WMM_NUM_AC ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,void*,...) ; 
 scalar_t__ ath6kl_hif_enable_scatter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_warn (char*,int) ; 
 void* min (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void htc_setup_msg_bndl(struct htc_target *target)
{
	/* limit what HTC can handle */
	target->msg_per_bndl_max = min(HTC_HOST_MAX_MSG_PER_BUNDLE,
				       target->msg_per_bndl_max);

	if (ath6kl_hif_enable_scatter(target->dev->ar)) {
		target->msg_per_bndl_max = 0;
		return;
	}

	/* limit bundle what the device layer can handle */
	target->msg_per_bndl_max = min(target->max_scat_entries,
				       target->msg_per_bndl_max);

	ath6kl_dbg(ATH6KL_DBG_BOOT,
		   "htc bundling allowed msg_per_bndl_max %d\n",
		   target->msg_per_bndl_max);

	/* Max rx bundle size is limited by the max tx bundle size */
	target->max_rx_bndl_sz = target->max_xfer_szper_scatreq;
	/* Max tx bundle size if limited by the extended mbox address range */
	target->max_tx_bndl_sz = min(HIF_MBOX0_EXT_WIDTH,
				     target->max_xfer_szper_scatreq);

	ath6kl_dbg(ATH6KL_DBG_BOOT, "htc max_rx_bndl_sz %d max_tx_bndl_sz %d\n",
		   target->max_rx_bndl_sz, target->max_tx_bndl_sz);

	if (target->max_tx_bndl_sz)
		/* tx_bndl_mask is enabled per AC, each has 1 bit */
		target->tx_bndl_mask = (1 << WMM_NUM_AC) - 1;

	if (target->max_rx_bndl_sz)
		target->rx_bndl_enable = true;

	if ((target->tgt_cred_sz % target->block_sz) != 0) {
		ath6kl_warn("credit size: %d is not block aligned! Disabling send bundling\n",
			    target->tgt_cred_sz);

		/*
		 * Disallow send bundling since the credit size is
		 * not aligned to a block size the I/O block
		 * padding will spill into the next credit buffer
		 * which is fatal.
		 */
		target->tx_bndl_mask = 0;
	}
}