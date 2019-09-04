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
struct ethtool_channels {int /*<<< orphan*/  tx_count; int /*<<< orphan*/  rx_count; int /*<<< orphan*/  max_tx; int /*<<< orphan*/  max_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  SXGBE_MAX_RX_CHANNELS ; 
 int /*<<< orphan*/  SXGBE_MAX_TX_CHANNELS ; 
 int /*<<< orphan*/  SXGBE_RX_QUEUES ; 
 int /*<<< orphan*/  SXGBE_TX_QUEUES ; 

__attribute__((used)) static void sxgbe_get_channels(struct net_device *dev,
			       struct ethtool_channels *channel)
{
	channel->max_rx = SXGBE_MAX_RX_CHANNELS;
	channel->max_tx = SXGBE_MAX_TX_CHANNELS;
	channel->rx_count = SXGBE_RX_QUEUES;
	channel->tx_count = SXGBE_TX_QUEUES;
}