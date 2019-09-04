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
struct xlgmac_hw_ops {int /*<<< orphan*/  (* config_rx_mode ) (struct xlgmac_pdata*) ;} ;
struct xlgmac_pdata {struct xlgmac_hw_ops hw_ops; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct xlgmac_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct xlgmac_pdata*) ; 

__attribute__((used)) static void xlgmac_set_rx_mode(struct net_device *netdev)
{
	struct xlgmac_pdata *pdata = netdev_priv(netdev);
	struct xlgmac_hw_ops *hw_ops = &pdata->hw_ops;

	hw_ops->config_rx_mode(pdata);
}