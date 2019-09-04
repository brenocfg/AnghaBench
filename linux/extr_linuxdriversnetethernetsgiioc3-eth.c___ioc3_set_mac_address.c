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
struct net_device {int* dev_addr; } ;
struct ioc3_private {struct ioc3* regs; } ;
struct ioc3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioc3_w_emar_h (int) ; 
 int /*<<< orphan*/  ioc3_w_emar_l (int) ; 
 struct ioc3_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void __ioc3_set_mac_address(struct net_device *dev)
{
	struct ioc3_private *ip = netdev_priv(dev);
	struct ioc3 *ioc3 = ip->regs;

	ioc3_w_emar_h((dev->dev_addr[5] <<  8) | dev->dev_addr[4]);
	ioc3_w_emar_l((dev->dev_addr[3] << 24) | (dev->dev_addr[2] << 16) |
	              (dev->dev_addr[1] <<  8) | dev->dev_addr[0]);
}