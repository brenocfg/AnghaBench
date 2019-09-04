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
struct usbnet {int /*<<< orphan*/ * net; scalar_t__* data; } ;
struct cdc_ncm_ctx {scalar_t__ tx_timer_pending; int /*<<< orphan*/  mtx; int /*<<< orphan*/  tx_reason_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdc_ncm_tx_timeout_start (struct cdc_ncm_ctx*) ; 
 int /*<<< orphan*/  netif_tx_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbnet_start_xmit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cdc_ncm_txpath_bh(unsigned long param)
{
	struct usbnet *dev = (struct usbnet *)param;
	struct cdc_ncm_ctx *ctx = (struct cdc_ncm_ctx *)dev->data[0];

	spin_lock_bh(&ctx->mtx);
	if (ctx->tx_timer_pending != 0) {
		ctx->tx_timer_pending--;
		cdc_ncm_tx_timeout_start(ctx);
		spin_unlock_bh(&ctx->mtx);
	} else if (dev->net != NULL) {
		ctx->tx_reason_timeout++;	/* count reason for transmitting */
		spin_unlock_bh(&ctx->mtx);
		netif_tx_lock_bh(dev->net);
		usbnet_start_xmit(NULL, dev->net);
		netif_tx_unlock_bh(dev->net);
	} else {
		spin_unlock_bh(&ctx->mtx);
	}
}