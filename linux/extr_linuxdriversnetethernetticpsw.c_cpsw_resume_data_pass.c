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
struct net_device {int dummy; } ;
struct cpsw_slave {scalar_t__ ndev; } ;
struct cpsw_priv {struct cpsw_common* cpsw; } ;
struct TYPE_2__ {int slaves; } ;
struct cpsw_common {struct cpsw_slave* slaves; TYPE_1__ data; int /*<<< orphan*/  dma; scalar_t__ usage_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpdma_ctlr_start (int /*<<< orphan*/ ) ; 
 int cpsw_fill_rx_channels (struct cpsw_priv*) ; 
 int /*<<< orphan*/  cpsw_intr_enable (struct cpsw_common*) ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dormant_off (scalar_t__) ; 
 scalar_t__ netif_running (scalar_t__) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (scalar_t__) ; 

__attribute__((used)) static int cpsw_resume_data_pass(struct net_device *ndev)
{
	struct cpsw_priv *priv = netdev_priv(ndev);
	struct cpsw_common *cpsw = priv->cpsw;
	struct cpsw_slave *slave;
	int i, ret;

	/* Allow rx packets handling */
	for (i = cpsw->data.slaves, slave = cpsw->slaves; i; i--, slave++)
		if (slave->ndev && netif_running(slave->ndev))
			netif_dormant_off(slave->ndev);

	/* After this receive is started */
	if (cpsw->usage_count) {
		ret = cpsw_fill_rx_channels(priv);
		if (ret)
			return ret;

		cpdma_ctlr_start(cpsw->dma);
		cpsw_intr_enable(cpsw);
	}

	/* Resume transmit for every affected interface */
	for (i = cpsw->data.slaves, slave = cpsw->slaves; i; i--, slave++)
		if (slave->ndev && netif_running(slave->ndev))
			netif_tx_start_all_queues(slave->ndev);

	return 0;
}