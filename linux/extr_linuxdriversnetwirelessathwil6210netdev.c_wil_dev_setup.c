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
struct net_device {int /*<<< orphan*/  tx_queue_len; int /*<<< orphan*/  max_mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIL_TX_Q_LEN_DEFAULT ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  mtu_max ; 

__attribute__((used)) static void wil_dev_setup(struct net_device *dev)
{
	ether_setup(dev);
	dev->max_mtu = mtu_max;
	dev->tx_queue_len = WIL_TX_Q_LEN_DEFAULT;
}