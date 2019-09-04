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
struct TYPE_4__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_urb; } ;
typedef  TYPE_2__ rtl8150_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  usb_unlink_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl8150_tx_timeout(struct net_device *netdev)
{
	rtl8150_t *dev = netdev_priv(netdev);
	dev_warn(&netdev->dev, "Tx timeout.\n");
	usb_unlink_urb(dev->tx_urb);
	netdev->stats.tx_errors++;
}