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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int EPROTONOSUPPORT ; 
 scalar_t__ ETH_ALEN ; 
 int /*<<< orphan*/  ETH_P_8021AD ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 size_t IFLA_ADDRESS ; 
 size_t IFLA_BR_VLAN_DEFAULT_PVID ; 
 size_t IFLA_BR_VLAN_PROTOCOL ; 
 scalar_t__ VLAN_VID_MASK ; 
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int nla_get_be16 (struct nlattr*) ; 
 scalar_t__ nla_get_u16 (struct nlattr*) ; 
 scalar_t__ nla_len (struct nlattr*) ; 

__attribute__((used)) static int br_validate(struct nlattr *tb[], struct nlattr *data[],
		       struct netlink_ext_ack *extack)
{
	if (tb[IFLA_ADDRESS]) {
		if (nla_len(tb[IFLA_ADDRESS]) != ETH_ALEN)
			return -EINVAL;
		if (!is_valid_ether_addr(nla_data(tb[IFLA_ADDRESS])))
			return -EADDRNOTAVAIL;
	}

	if (!data)
		return 0;

#ifdef CONFIG_BRIDGE_VLAN_FILTERING
	if (data[IFLA_BR_VLAN_PROTOCOL]) {
		switch (nla_get_be16(data[IFLA_BR_VLAN_PROTOCOL])) {
		case htons(ETH_P_8021Q):
		case htons(ETH_P_8021AD):
			break;
		default:
			return -EPROTONOSUPPORT;
		}
	}

	if (data[IFLA_BR_VLAN_DEFAULT_PVID]) {
		__u16 defpvid = nla_get_u16(data[IFLA_BR_VLAN_DEFAULT_PVID]);

		if (defpvid >= VLAN_VID_MASK)
			return -EINVAL;
	}
#endif

	return 0;
}