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
struct mt76_dev {int /*<<< orphan*/  macaddr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_random_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 

void
mt76_eeprom_override(struct mt76_dev *dev)
{
#ifdef CONFIG_OF
	struct device_node *np = dev->dev->of_node;
	const u8 *mac;

	if (!np)
		return;

	mac = of_get_mac_address(np);
	if (mac)
		memcpy(dev->macaddr, mac, ETH_ALEN);
#endif

	if (!is_valid_ether_addr(dev->macaddr)) {
		eth_random_addr(dev->macaddr);
		dev_info(dev->dev,
			 "Invalid MAC address, using random address %pM\n",
			 dev->macaddr);
	}
}