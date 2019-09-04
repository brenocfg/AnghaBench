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
struct tlan_priv {scalar_t__ tx_list; scalar_t__ rx_list; int /*<<< orphan*/  tx_busy_count; int /*<<< orphan*/  rx_eoc_count; } ;
struct net_device_stats {int dummy; } ;
struct net_device {struct net_device_stats stats; int /*<<< orphan*/  base_addr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLAN_DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TLAN_DEBUG_GNRL ; 
 int TLAN_DEBUG_LIST ; 
 int /*<<< orphan*/  TLAN_DEBUG_RX ; 
 int /*<<< orphan*/  TLAN_DEBUG_TX ; 
 int TLAN_NUM_RX_LISTS ; 
 int TLAN_NUM_TX_LISTS ; 
 int /*<<< orphan*/  TLAN_RECORD ; 
 int debug ; 
 struct tlan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tlan_phy_print (struct net_device*) ; 
 int /*<<< orphan*/  tlan_print_dio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlan_print_list (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  tlan_read_and_clear_stats (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct net_device_stats *tlan_get_stats(struct net_device *dev)
{
	struct tlan_priv	*priv = netdev_priv(dev);
	int i;

	/* Should only read stats if open ? */
	tlan_read_and_clear_stats(dev, TLAN_RECORD);

	TLAN_DBG(TLAN_DEBUG_RX, "RECEIVE:  %s EOC count = %d\n", dev->name,
		 priv->rx_eoc_count);
	TLAN_DBG(TLAN_DEBUG_TX, "TRANSMIT:  %s Busy count = %d\n", dev->name,
		 priv->tx_busy_count);
	if (debug & TLAN_DEBUG_GNRL) {
		tlan_print_dio(dev->base_addr);
		tlan_phy_print(dev);
	}
	if (debug & TLAN_DEBUG_LIST) {
		for (i = 0; i < TLAN_NUM_RX_LISTS; i++)
			tlan_print_list(priv->rx_list + i, "RX", i);
		for (i = 0; i < TLAN_NUM_TX_LISTS; i++)
			tlan_print_list(priv->tx_list + i, "TX", i);
	}

	return &dev->stats;

}