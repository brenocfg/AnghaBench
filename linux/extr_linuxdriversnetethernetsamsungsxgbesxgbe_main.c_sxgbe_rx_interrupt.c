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
struct sxgbe_rx_queue {int /*<<< orphan*/  queue_no; struct sxgbe_priv_data* priv_ptr; } ;
struct TYPE_8__ {int rx_threshold; } ;
struct sxgbe_priv_data {int rx_tc; TYPE_4__ xstats; int /*<<< orphan*/  ioaddr; TYPE_3__* hw; int /*<<< orphan*/  napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_7__ {TYPE_2__* mtl; TYPE_1__* dma; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_rx_mtl_mode ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_5__ {int (* rx_dma_int_status ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ;int /*<<< orphan*/  (* disable_dma_irq ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int SXGBE_MTL_SFMODE ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int handle_rx ; 
 scalar_t__ likely (int) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 int rx_bump_tc ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t sxgbe_rx_interrupt(int irq, void *dev_id)
{
	int status;
	struct sxgbe_rx_queue *rxq = (struct sxgbe_rx_queue *)dev_id;
	struct sxgbe_priv_data *priv = rxq->priv_ptr;

	/* get the channel status */
	status = priv->hw->dma->rx_dma_int_status(priv->ioaddr, rxq->queue_no,
						  &priv->xstats);

	if (likely((status & handle_rx) && (napi_schedule_prep(&priv->napi)))) {
		priv->hw->dma->disable_dma_irq(priv->ioaddr, rxq->queue_no);
		__napi_schedule(&priv->napi);
	}

	/* check for TC configuration change */
	if (unlikely((status & rx_bump_tc) &&
		     (priv->rx_tc != SXGBE_MTL_SFMODE) &&
		     (priv->rx_tc < 128))) {
		/* step of TC is 32 */
		priv->rx_tc += 32;
		priv->hw->mtl->set_rx_mtl_mode(priv->ioaddr,
					       rxq->queue_no, priv->rx_tc);
		priv->xstats.rx_threshold = priv->rx_tc;
	}

	return IRQ_HANDLED;
}