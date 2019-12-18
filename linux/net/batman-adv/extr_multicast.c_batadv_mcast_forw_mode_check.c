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
struct sk_buff {int dummy; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; } ;
struct batadv_priv {int /*<<< orphan*/  multicast_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_IPV6 ; 
 int EINVAL ; 
#define  ETH_P_IP 129 
#define  ETH_P_IPV6 128 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int batadv_mcast_forw_mode_check_ipv4 (struct batadv_priv*,struct sk_buff*,int*,int*) ; 
 int batadv_mcast_forw_mode_check_ipv6 (struct batadv_priv*,struct sk_buff*,int*,int*) ; 
 struct ethhdr* eth_hdr (struct sk_buff*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int batadv_mcast_forw_mode_check(struct batadv_priv *bat_priv,
					struct sk_buff *skb,
					bool *is_unsnoopable,
					int *is_routable)
{
	struct ethhdr *ethhdr = eth_hdr(skb);

	if (!atomic_read(&bat_priv->multicast_mode))
		return -EINVAL;

	switch (ntohs(ethhdr->h_proto)) {
	case ETH_P_IP:
		return batadv_mcast_forw_mode_check_ipv4(bat_priv, skb,
							 is_unsnoopable,
							 is_routable);
	case ETH_P_IPV6:
		if (!IS_ENABLED(CONFIG_IPV6))
			return -EINVAL;

		return batadv_mcast_forw_mode_check_ipv6(bat_priv, skb,
							 is_unsnoopable,
							 is_routable);
	default:
		return -EINVAL;
	}
}