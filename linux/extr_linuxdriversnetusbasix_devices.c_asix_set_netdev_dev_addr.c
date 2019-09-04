#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct usbnet {TYPE_1__* net; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  eth_hw_addr_random (TYPE_1__*) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (TYPE_1__*,char*) ; 

__attribute__((used)) static void asix_set_netdev_dev_addr(struct usbnet *dev, u8 *addr)
{
	if (is_valid_ether_addr(addr)) {
		memcpy(dev->net->dev_addr, addr, ETH_ALEN);
	} else {
		netdev_info(dev->net, "invalid hw address, using random\n");
		eth_hw_addr_random(dev->net);
	}
}