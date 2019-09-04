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
struct TYPE_4__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_2__ stats; } ;
struct cpsw_priv {struct cpsw_common* cpsw; } ;
struct cpsw_common {int tx_ch_num; TYPE_1__* txv; } ;
struct TYPE_3__ {int /*<<< orphan*/  ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpdma_chan_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpdma_chan_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_err (struct cpsw_priv*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cpsw_intr_disable (struct cpsw_common*) ; 
 int /*<<< orphan*/  cpsw_intr_enable (struct cpsw_common*) ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  tx_err ; 

__attribute__((used)) static void cpsw_ndo_tx_timeout(struct net_device *ndev)
{
	struct cpsw_priv *priv = netdev_priv(ndev);
	struct cpsw_common *cpsw = priv->cpsw;
	int ch;

	cpsw_err(priv, tx_err, "transmit timeout, restarting dma\n");
	ndev->stats.tx_errors++;
	cpsw_intr_disable(cpsw);
	for (ch = 0; ch < cpsw->tx_ch_num; ch++) {
		cpdma_chan_stop(cpsw->txv[ch].ch);
		cpdma_chan_start(cpsw->txv[ch].ch);
	}

	cpsw_intr_enable(cpsw);
	netif_trans_update(ndev);
	netif_tx_wake_all_queues(ndev);
}