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
struct rtw_netdev_priv_indicator {int /*<<< orphan*/  priv; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct rtw_netdev_priv_indicator* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

void rtw_free_netdev(struct net_device *netdev)
{
	struct rtw_netdev_priv_indicator *pnpi;

	if (!netdev)
		goto RETURN;

	pnpi = netdev_priv(netdev);

	if (!pnpi->priv)
		goto RETURN;

	vfree(pnpi->priv);
	free_netdev(netdev);

RETURN:
	return;
}