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
typedef  int /*<<< orphan*/  u8 ;
struct macvlan_dev {size_t macaddr_count; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 size_t nla_total_size (int) ; 

__attribute__((used)) static size_t macvlan_get_size_mac(const struct macvlan_dev *vlan)
{
	if (vlan->macaddr_count == 0)
		return 0;
	return nla_total_size(0) /* IFLA_MACVLAN_MACADDR_DATA */
		+ vlan->macaddr_count * nla_total_size(sizeof(u8) * ETH_ALEN);
}