#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct mwifiex_private {scalar_t__ tx_timeout_cnt; TYPE_2__* adapter; int /*<<< orphan*/  bss_num; int /*<<< orphan*/  bss_type; int /*<<< orphan*/  num_tx_timeout; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* card_reset ) (TYPE_2__*) ;} ;
struct TYPE_5__ {TYPE_1__ if_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ TX_TIMEOUT_THRESHOLD ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mwifiex_dbg (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 struct mwifiex_private* mwifiex_netdev_get_priv (struct net_device*) ; 
 int /*<<< orphan*/  mwifiex_set_trans_start (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void
mwifiex_tx_timeout(struct net_device *dev)
{
	struct mwifiex_private *priv = mwifiex_netdev_get_priv(dev);

	priv->num_tx_timeout++;
	priv->tx_timeout_cnt++;
	mwifiex_dbg(priv->adapter, ERROR,
		    "%lu : Tx timeout(#%d), bss_type-num = %d-%d\n",
		    jiffies, priv->tx_timeout_cnt, priv->bss_type,
		    priv->bss_num);
	mwifiex_set_trans_start(dev);

	if (priv->tx_timeout_cnt > TX_TIMEOUT_THRESHOLD &&
	    priv->adapter->if_ops.card_reset) {
		mwifiex_dbg(priv->adapter, ERROR,
			    "tx_timeout_cnt exceeds threshold.\t"
			    "Triggering card reset!\n");
		priv->adapter->if_ops.card_reset(priv->adapter);
	}
}