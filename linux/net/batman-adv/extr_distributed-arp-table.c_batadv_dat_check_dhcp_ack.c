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
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int BATADV_BOOTREPLY ; 
 int BATADV_DHCPACK ; 
 int batadv_dat_check_dhcp (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_dat_dhcp_get_yiaddr (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_dat_get_dhcp_chaddr (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int batadv_dat_get_dhcp_message_type (struct sk_buff*) ; 

__attribute__((used)) static bool
batadv_dat_check_dhcp_ack(struct sk_buff *skb, __be16 proto, __be32 *ip_src,
			  u8 *chaddr, __be32 *yiaddr)
{
	int type;

	type = batadv_dat_check_dhcp(skb, proto, ip_src);
	if (type != BATADV_BOOTREPLY)
		return false;

	type = batadv_dat_get_dhcp_message_type(skb);
	if (type != BATADV_DHCPACK)
		return false;

	if (!batadv_dat_dhcp_get_yiaddr(skb, yiaddr))
		return false;

	if (!batadv_dat_get_dhcp_chaddr(skb, chaddr))
		return false;

	return true;
}