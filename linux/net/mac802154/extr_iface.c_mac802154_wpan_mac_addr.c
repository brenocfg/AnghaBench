#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_2__ {struct net_device* lowpan_dev; int /*<<< orphan*/  extended_addr; } ;
struct ieee802154_sub_if_data {TYPE_1__ wpan_dev; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 struct ieee802154_sub_if_data* IEEE802154_DEV_TO_SUB_IF (struct net_device*) ; 
 int /*<<< orphan*/  ieee802154_be64_to_le64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee802154_is_valid_extended_unicast_addr (int /*<<< orphan*/ ) ; 
 int mac802154_wpan_update_llsec (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int mac802154_wpan_mac_addr(struct net_device *dev, void *p)
{
	struct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	struct sockaddr *addr = p;
	__le64 extended_addr;

	if (netif_running(dev))
		return -EBUSY;

	/* lowpan need to be down for update
	 * SLAAC address after ifup
	 */
	if (sdata->wpan_dev.lowpan_dev) {
		if (netif_running(sdata->wpan_dev.lowpan_dev))
			return -EBUSY;
	}

	ieee802154_be64_to_le64(&extended_addr, addr->sa_data);
	if (!ieee802154_is_valid_extended_unicast_addr(extended_addr))
		return -EINVAL;

	memcpy(dev->dev_addr, addr->sa_data, dev->addr_len);
	sdata->wpan_dev.extended_addr = extended_addr;

	/* update lowpan interface mac address when
	 * wpan mac has been changed
	 */
	if (sdata->wpan_dev.lowpan_dev)
		memcpy(sdata->wpan_dev.lowpan_dev->dev_addr, dev->dev_addr,
		       dev->addr_len);

	return mac802154_wpan_update_llsec(dev);
}