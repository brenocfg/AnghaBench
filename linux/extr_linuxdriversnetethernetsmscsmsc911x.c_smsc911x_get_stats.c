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
struct smsc911x_data {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  rx_dropped; } ;
struct net_device {struct net_device_stats stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_DROP ; 
 struct smsc911x_data* netdev_priv (struct net_device*) ; 
 scalar_t__ smsc911x_reg_read (struct smsc911x_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc911x_tx_update_txcounters (struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *smsc911x_get_stats(struct net_device *dev)
{
	struct smsc911x_data *pdata = netdev_priv(dev);
	smsc911x_tx_update_txcounters(dev);
	dev->stats.rx_dropped += smsc911x_reg_read(pdata, RX_DROP);
	return &dev->stats;
}