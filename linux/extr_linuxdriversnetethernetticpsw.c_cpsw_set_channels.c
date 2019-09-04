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
struct ethtool_channels {int dummy; } ;
struct cpsw_slave {scalar_t__ ndev; } ;
struct cpsw_priv {int /*<<< orphan*/  dev; struct cpsw_common* cpsw; } ;
struct TYPE_2__ {int slaves; } ;
struct cpsw_common {scalar_t__ usage_count; int /*<<< orphan*/  rx_ch_num; int /*<<< orphan*/  tx_ch_num; struct cpsw_slave* slaves; TYPE_1__ data; } ;

/* Variables and functions */
 int cpsw_check_ch_settings (struct cpsw_common*,struct ethtool_channels*) ; 
 int cpsw_resume_data_pass (struct net_device*) ; 
 int /*<<< orphan*/  cpsw_split_res (struct net_device*) ; 
 int /*<<< orphan*/  cpsw_suspend_data_pass (struct net_device*) ; 
 int cpsw_update_channels (struct cpsw_priv*,struct ethtool_channels*) ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct cpsw_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (scalar_t__) ; 
 int netif_set_real_num_rx_queues (scalar_t__,int /*<<< orphan*/ ) ; 
 int netif_set_real_num_tx_queues (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpsw_set_channels(struct net_device *ndev,
			     struct ethtool_channels *chs)
{
	struct cpsw_priv *priv = netdev_priv(ndev);
	struct cpsw_common *cpsw = priv->cpsw;
	struct cpsw_slave *slave;
	int i, ret;

	ret = cpsw_check_ch_settings(cpsw, chs);
	if (ret < 0)
		return ret;

	cpsw_suspend_data_pass(ndev);
	ret = cpsw_update_channels(priv, chs);
	if (ret)
		goto err;

	for (i = cpsw->data.slaves, slave = cpsw->slaves; i; i--, slave++) {
		if (!(slave->ndev && netif_running(slave->ndev)))
			continue;

		/* Inform stack about new count of queues */
		ret = netif_set_real_num_tx_queues(slave->ndev,
						   cpsw->tx_ch_num);
		if (ret) {
			dev_err(priv->dev, "cannot set real number of tx queues\n");
			goto err;
		}

		ret = netif_set_real_num_rx_queues(slave->ndev,
						   cpsw->rx_ch_num);
		if (ret) {
			dev_err(priv->dev, "cannot set real number of rx queues\n");
			goto err;
		}
	}

	if (cpsw->usage_count)
		cpsw_split_res(ndev);

	ret = cpsw_resume_data_pass(ndev);
	if (!ret)
		return 0;
err:
	dev_err(priv->dev, "cannot update channels number, closing device\n");
	dev_close(ndev);
	return ret;
}