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
struct net_device {int dummy; } ;
struct ethtool_coalesce {unsigned int tx_coalesce_usecs; unsigned int tx_coalesce_usecs_irq; unsigned int rx_coalesce_usecs; unsigned int rx_coalesce_usecs_irq; int use_adaptive_rx_coalesce; } ;
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ef4_get_irq_moderation (struct ef4_nic*,unsigned int*,unsigned int*,int*) ; 
 struct ef4_nic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ef4_ethtool_get_coalesce(struct net_device *net_dev,
				    struct ethtool_coalesce *coalesce)
{
	struct ef4_nic *efx = netdev_priv(net_dev);
	unsigned int tx_usecs, rx_usecs;
	bool rx_adaptive;

	ef4_get_irq_moderation(efx, &tx_usecs, &rx_usecs, &rx_adaptive);

	coalesce->tx_coalesce_usecs = tx_usecs;
	coalesce->tx_coalesce_usecs_irq = tx_usecs;
	coalesce->rx_coalesce_usecs = rx_usecs;
	coalesce->rx_coalesce_usecs_irq = rx_usecs;
	coalesce->use_adaptive_rx_coalesce = rx_adaptive;

	return 0;
}