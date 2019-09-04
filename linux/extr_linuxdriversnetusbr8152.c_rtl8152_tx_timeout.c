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
struct r8152 {int /*<<< orphan*/  intf; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct r8152* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_warn (struct r8152*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  tx_err ; 
 int /*<<< orphan*/  usb_queue_reset_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl8152_tx_timeout(struct net_device *netdev)
{
	struct r8152 *tp = netdev_priv(netdev);

	netif_warn(tp, tx_err, netdev, "Tx timeout\n");

	usb_queue_reset_device(tp->intf);
}