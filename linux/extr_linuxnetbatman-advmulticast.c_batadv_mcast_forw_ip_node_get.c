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
struct ethhdr {int /*<<< orphan*/  h_proto; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int dummy; } ;

/* Variables and functions */
#define  ETH_P_IP 129 
#define  ETH_P_IPV6 128 
 struct batadv_orig_node* batadv_mcast_forw_ipv4_node_get (struct batadv_priv*) ; 
 struct batadv_orig_node* batadv_mcast_forw_ipv6_node_get (struct batadv_priv*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct batadv_orig_node *
batadv_mcast_forw_ip_node_get(struct batadv_priv *bat_priv,
			      struct ethhdr *ethhdr)
{
	switch (ntohs(ethhdr->h_proto)) {
	case ETH_P_IP:
		return batadv_mcast_forw_ipv4_node_get(bat_priv);
	case ETH_P_IPV6:
		return batadv_mcast_forw_ipv6_node_get(bat_priv);
	default:
		/* we shouldn't be here... */
		return NULL;
	}
}