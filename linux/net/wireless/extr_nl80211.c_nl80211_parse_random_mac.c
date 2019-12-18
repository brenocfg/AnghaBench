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
typedef  int u8 ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_ALEN ; 
 size_t NL80211_ATTR_MAC ; 
 size_t NL80211_ATTR_MAC_MASK ; 
 int /*<<< orphan*/  eth_zero_addr (int*) ; 
 scalar_t__ is_multicast_ether_addr (int*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 

int nl80211_parse_random_mac(struct nlattr **attrs,
			     u8 *mac_addr, u8 *mac_addr_mask)
{
	int i;

	if (!attrs[NL80211_ATTR_MAC] && !attrs[NL80211_ATTR_MAC_MASK]) {
		eth_zero_addr(mac_addr);
		eth_zero_addr(mac_addr_mask);
		mac_addr[0] = 0x2;
		mac_addr_mask[0] = 0x3;

		return 0;
	}

	/* need both or none */
	if (!attrs[NL80211_ATTR_MAC] || !attrs[NL80211_ATTR_MAC_MASK])
		return -EINVAL;

	memcpy(mac_addr, nla_data(attrs[NL80211_ATTR_MAC]), ETH_ALEN);
	memcpy(mac_addr_mask, nla_data(attrs[NL80211_ATTR_MAC_MASK]), ETH_ALEN);

	/* don't allow or configure an mcast address */
	if (!is_multicast_ether_addr(mac_addr_mask) ||
	    is_multicast_ether_addr(mac_addr))
		return -EINVAL;

	/*
	 * allow users to pass a MAC address that has bits set outside
	 * of the mask, but don't bother drivers with having to deal
	 * with such bits
	 */
	for (i = 0; i < ETH_ALEN; i++)
		mac_addr[i] &= mac_addr_mask[i];

	return 0;
}