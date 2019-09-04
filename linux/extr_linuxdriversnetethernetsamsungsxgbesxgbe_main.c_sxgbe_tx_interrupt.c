#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sxgbe_tx_queue {int /*<<< orphan*/  queue_no; struct sxgbe_priv_data* priv_ptr; } ;
struct TYPE_8__ {int tx_threshold; } ;
struct sxgbe_priv_data {int tx_tc; TYPE_4__ xstats; int /*<<< orphan*/  ioaddr; TYPE_3__* hw; int /*<<< orphan*/  napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_7__ {TYPE_2__* mtl; TYPE_1__* dma; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_tx_mtl_mode ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_5__ {int (* tx_dma_int_status ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int SXGBE_MTL_SFMODE ; 
 int handle_tx ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sxgbe_restart_tx_queue (struct sxgbe_priv_data*,int /*<<< orphan*/ ) ; 
 int tx_bump_tc ; 
 int tx_hard_error ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t sxgbe_tx_interrupt(int irq, void *dev_id)
{
	int status;
	struct sxgbe_tx_queue *txq = (struct sxgbe_tx_queue *)dev_id;
	struct sxgbe_priv_data *priv = txq->priv_ptr;

	/* get the channel status */
	status = priv->hw->dma->tx_dma_int_status(priv->ioaddr, txq->queue_no,
						  &priv->xstats);
	/* check for normal path */
	if (likely((status & handle_tx)))
		napi_schedule(&priv->napi);

	/* check for unrecoverable error */
	if (unlikely((status & tx_hard_error)))
		sxgbe_restart_tx_queue(priv, txq->queue_no);

	/* check for TC configuration change */
	if (unlikely((status & tx_bump_tc) &&
		     (priv->tx_tc != SXGBE_MTL_SFMODE) &&
		     (priv->tx_tc < 512))) {
		/* step of TX TC is 32 till 128, otherwise 64 */
		priv->tx_tc += (priv->tx_tc < 128) ? 32 : 64;
		priv->hw->mtl->set_tx_mtl_mode(priv->ioaddr,
					       txq->queue_no, priv->tx_tc);
		priv->xstats.tx_threshold = priv->tx_tc;
	}

	return IRQ_HANDLED;
}